/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

extern void sea_dsa_alias(const void *p, ...);

#define ARRAY_SIZE 5

int main() {
    size_t nd_ary_sz = nd_size_t();
    assume(nd_ary_sz <= ARRAY_SIZE);
    struct aws_byte_buf tos[nd_ary_sz];
    for (size_t i = 0; i < nd_ary_sz; i++) {
        initialize_byte_buf(&tos[i]);
        assume(aws_byte_buf_is_valid(&tos[i]));
    }

    /* save current state of the data structure */
    struct aws_byte_buf tos_old[nd_ary_sz];
    memcpy(&tos_old, &tos, sizeof(struct aws_byte_buf) * nd_ary_sz);

    struct aws_byte_cursor froms[nd_ary_sz];
    for (size_t i = 0; i < nd_ary_sz; i++) {
        initialize_byte_cursor(&froms[i]);
        assume(aws_byte_cursor_is_valid(&froms[i]));
    }

    /* save current state of the data structure */
    struct aws_byte_cursor froms_old[nd_ary_sz];
    memcpy(&froms_old, &froms, sizeof(struct aws_byte_cursor) * nd_ary_sz);

    for (size_t i = 0; i < nd_ary_sz; i++) {
        if (aws_byte_buf_append(&tos[i], &froms[i]) == AWS_OP_SUCCESS) {
            sassert(tos[i].len == tos_old[i].len + froms[i].len);
        } else {
            /* if the operation return an error, to must not change */
            // assert_bytes_match(tos_old[i].buffer, tos[i].buffer, tos[i].len);
            sassert(tos_old[i].len == tos[i].len);
        }

        sassert(aws_byte_buf_is_valid(&tos[i]));
        sassert(aws_byte_cursor_is_valid(&froms[i]));
        sassert(tos_old[i].allocator == tos[i].allocator);
        sassert(tos_old[i].capacity == tos[i].capacity);
        // assert_bytes_match(froms_old[i].ptr, froms[i].ptr, froms[i].len);
        sassert(froms_old[i].len == froms[i].len);
    }

    return 0;
}
