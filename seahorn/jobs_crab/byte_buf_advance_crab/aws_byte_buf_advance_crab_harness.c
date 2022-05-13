/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

extern void sea_dsa_alias(const void *p, ...);

int main() {
    /* parameters */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);
    struct aws_byte_buf output;
    size_t len = nd_size_t();

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));
    if (nd_bool()) {
        output = buf;
    } else {
        initialize_byte_buf(&output);
        assume(aws_byte_buf_is_valid(&output));
    }

    /* save current state of the parameters */
    struct aws_byte_buf old = buf;
    struct store_byte_from_buffer old_byte_from_buf;
    save_byte_from_array(buf.buffer, buf.len, &old_byte_from_buf);

    sea_dsa_alias(&old,&buf,&output);

    /* operation under verification */
    if (aws_byte_buf_advance(&buf, &output, len)) {
        sassert(buf.len == old.len + len);
        sassert(buf.capacity == old.capacity);
        sassert(buf.allocator == old.allocator);
        if (old.len > 0) {
            assert_byte_from_buffer_matches(buf.buffer, &old_byte_from_buf);
        }
        sassert(output.len == 0);
        sassert(output.capacity == len);
        sassert(output.allocator == NULL);
    } else {
        assert_byte_buf_equivalence(&buf, &old, &old_byte_from_buf);
        sassert(output.len == 0);
        sassert(output.capacity == 0);
        sassert(output.allocator == NULL);
        sassert(output.buffer == NULL);
    }
    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_buf_is_valid(&output));

    return 0;
}
