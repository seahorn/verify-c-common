/*
 * 
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>
#include <nondet.h>
#include <config.h>

#define SIZE MAX_ARRAY_SIZE

int main() {
    /* parameters */
    struct aws_byte_buf *buf_ary[SIZE];
    #pragma unroll 1
    for (unsigned i = 0; i < SIZE; ++i) {
        struct aws_byte_buf *tmp = malloc(sizeof(struct aws_byte_buf));
        initialize_byte_buf(tmp);
        assume(aws_byte_buf_is_valid(tmp));
        buf_ary[i] = tmp;
    }
    uint8_t idx = nd_uint8_t();
    assume(idx < SIZE);
    struct aws_byte_buf *to = buf_ary[idx];

    /* save current state of the data structure */
    struct aws_byte_buf to_old = *to;

    struct aws_byte_cursor *cursor_ary[SIZE];
    #pragma unroll 1
    for (unsigned i = 0; i < SIZE; ++i) {
        struct aws_byte_cursor *tmp = malloc(sizeof(struct aws_byte_cursor));
        initialize_byte_cursor(tmp);
        assume(aws_byte_cursor_is_valid(tmp));
        cursor_ary[i] = tmp;
    }
    uint8_t idx2 = nd_uint8_t();
    assume(idx2 < SIZE);
    struct aws_byte_cursor *from = cursor_ary[idx2];

    /* save current state of the data structure */
    struct aws_byte_cursor from_old = *from;

    if (aws_byte_buf_append(to, from) == AWS_OP_SUCCESS) {
        sassert(to->len == to_old.len + from->len);
    } else {
        /* if the operation return an error, to must not change */
        assert_bytes_match(to_old.buffer, to->buffer, to->len);
        sassert(to_old.len == to->len);
    }

    sassert(aws_byte_buf_is_valid(to));
    sassert(aws_byte_cursor_is_valid(from));
    sassert(to_old.allocator == to->allocator);
    sassert(to_old.capacity == to->capacity);
    assert_bytes_match(from_old.ptr, from->ptr, from->len);
    sassert(from_old.len == from->len);

    return 0;
}
