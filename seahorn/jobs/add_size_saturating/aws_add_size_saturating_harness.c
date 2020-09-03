#include <aws/common/math.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

/**
 */
int main() {
    if (nd_bool()) {
        uint64_t a = nd_uint64_t();
        uint64_t b = nd_uint64_t();
        uint64_t r = aws_add_u64_saturating(a, b);
        if ((b > 0) && (a > (UINT64_MAX - b))) {
            sassert(r == UINT64_MAX);
        } else {
            sassert(r == a + b);
        }
    } else {
        uint32_t a = nd_uint32_t();
        uint32_t b = nd_uint32_t();
        uint32_t r = aws_add_u32_saturating(a, b);
        if ((b > 0) && (a > (UINT32_MAX - b))) {
            sassert(r == UINT32_MAX);
        } else {
            sassert(r == a + b);
        }
    }
    return 0;
}
