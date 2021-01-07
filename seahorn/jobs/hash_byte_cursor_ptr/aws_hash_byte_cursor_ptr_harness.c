#include <aws/common/hash_table.h>
#include <aws/common/byte_buf.h>

#include <seahorn/seahorn.h>

#include <byte_buf_helper.h>
#include <config.h>

int main(void) {
    struct aws_byte_cursor cur;
    initialize_byte_cursor_aligned(&cur);

    assume(aws_byte_cursor_is_bounded(&cur, MAX_BUFFER_SIZE));
    assume(aws_byte_cursor_is_valid(&cur));

    /* This function has no pre or post conditions */
    uint64_t rval = aws_hash_byte_cursor_ptr(&cur);

    sassert(aws_byte_cursor_is_valid(&cur));
    return 0;
}
