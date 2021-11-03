/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <proof_allocators.h>

int main() {
    /* data structure */
    struct aws_byte_buf *dest = (struct aws_byte_buf *)bounded_malloc_havoc(sizeof(*dest));

    /* parameters */
    struct aws_allocator *allocator = sea_allocator();
    struct aws_byte_buf src;
    initialize_byte_buf(&src);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&src));

    /* save current state of the data structure */
    struct store_byte_from_buffer old_byte;
    save_byte_from_array(src.buffer, src.len, &old_byte);

    sea_tracking_on();

    /* operation under verification */
    if (!aws_byte_buf_init_copy(dest, allocator, &src)) {
        /* assertions */
        sassert(aws_byte_buf_is_valid(dest));
        sassert(aws_byte_buf_has_allocator(dest));
        sassert(dest->len == src.len);
        sassert(dest->capacity == src.capacity);
        assert_bytes_match(dest->buffer, src.buffer, dest->len);
        sassert(aws_byte_buf_is_valid(&src));
        if (src.len > 0) {
            sassert(!sea_is_modified((char *)&src));
            sassert(!sea_is_modified((char *)src.buffer));
            assert_byte_from_buffer_matches(dest->buffer, &old_byte);
        }
    }

    return 0;
}
