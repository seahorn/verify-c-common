#include <seahorn/seahorn.h>
#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <proof_allocators.h>
#include <utils.h>

int main(void) {
    struct aws_byte_cursor cur;
    initialize_byte_cursor(&cur);

    assume(aws_byte_cursor_is_bounded(&cur, MAX_CURSOR_SIZE));
    assume(aws_byte_cursor_is_valid(&cur));

    /* This function has no pre or post conditions */
    uint64_t rval = aws_hash_byte_cursor_ptr(&cur);

    sassert(aws_byte_cursor_is_valid(&cur));
}