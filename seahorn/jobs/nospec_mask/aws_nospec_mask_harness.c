/*
 */

#include <aws/common/byte_buf.h>
#include <aws/common/private/byte_buf.h>

#include <seahorn/seahorn.h>
#include <nondet.h>

int main() {
    /* parameters */
    size_t index = nd_size_t();
    size_t bound = nd_size_t();

    /* operation under verification */
    size_t rval = aws_nospec_mask(index, bound);

    /* assertions */
    if (rval == 0) {
        sassert((index >= bound) || (bound > (SIZE_MAX / 2)) || (index > (SIZE_MAX / 2)));
    } else {
        sassert(rval == UINTPTR_MAX);
        sassert(!((index >= bound) || (bound > (SIZE_MAX / 2)) || (index > (SIZE_MAX / 2))));
    }
    return 0;
}
