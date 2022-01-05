/**
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <proof_allocators.h>
#include <byte_buf_helper.h>
#include <utils.h>

#if defined __KLEE__ || defined __FUZZ__ || defined(__SYMBIOTIC__)
bool uninterpreted_predicate_fn(uint8_t value) {
    return nd_bool();
}
#endif

int main() {
    /* parameters */
    struct aws_byte_cursor cur;
    initialize_byte_cursor(&cur);

    /* assumptions */
    assume(aws_byte_cursor_is_bounded(&cur, MAX_BUFFER_SIZE));
    assume(aws_byte_cursor_is_valid(&cur));

    /* save current state of the data structure */
    struct store_byte_from_buffer old_byte_from_cur;
    save_byte_from_array(cur.ptr, cur.len, &old_byte_from_cur);

    /* operation under verification */
    struct aws_byte_cursor rv = aws_byte_cursor_trim_pred(&cur, uninterpreted_predicate_fn);

    /* assertions */
    sassert(aws_byte_cursor_is_valid(&cur));
    sassert(aws_byte_cursor_is_valid(&rv));
    if (cur.len > 0) {
        assert_byte_from_buffer_matches(cur.ptr, &old_byte_from_cur);
    }
    return 0;
}