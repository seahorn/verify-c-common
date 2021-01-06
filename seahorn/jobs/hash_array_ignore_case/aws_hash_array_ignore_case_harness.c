#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include "utils.h"
#include "proof_allocators.h"

int main(void) {
    /* parameters */
    size_t length = nd_size_t();
    assume(length < MAX_BUFFER_SIZE);
    uint8_t *array = can_fail_malloc(length);
    assume(AWS_MEM_IS_READABLE(array, length));

    /* operation under verification */
    uint64_t rval = aws_hash_array_ignore_case(array, length);

    /* assertions */
    sassert(AWS_MEM_IS_READABLE(array, length));
}