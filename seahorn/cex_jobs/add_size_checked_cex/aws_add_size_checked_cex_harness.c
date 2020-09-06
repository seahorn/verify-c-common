#include <aws/common/math.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

/**
 */
int main() {
    if (nd_bool()) {
        uint64_t a = nd_uint64_t();
        uint64_t b = nd_uint64_t();
        uint64_t r = nd_uint64_t();
        int rval = aws_add_u64_checked(a, b, &r);
        if (rval) {
            sassert(r == a + b);
        } else {
            sassert((b > 0) && (a > (UINT64_MAX - b)));
        }
    } else {
        uint32_t a = nd_uint32_t();
        uint32_t b = nd_uint32_t();
        uint32_t r = nd_uint32_t();
        if (!aws_add_u32_checked(a, b, &r)) {
            sassert(r == a + b);
        } else {
            sassert((b > 0) && (a > (UINT32_MAX - b)));
        }
    }
  return 0;
}
