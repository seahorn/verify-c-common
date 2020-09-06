#include <aws/common/math.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

/**
 */
int main() {
    if (nd_bool()) {
        /*
         * In this particular case, full range of nd inputs leads
         * to excessively long runtimes, so use 0 or UINT64_MAX instead.
         * AG: for arbitrary 'a' reduced to proving equivalence of multipliers
         * AG: all solvers tried blast multipliers and get stuck
         */
        uint64_t a = (nd_int()) ? 0 : UINT64_MAX;
        uint64_t b = nd_uint64_t();
        uint64_t r = aws_mul_u64_saturating(a, b);
        if (a > 0 && b > 0 && a > (UINT64_MAX / b)) {
            sassert(r == UINT64_MAX);
        } else {
            sassert(r == 0); // wrong assertion: expected cex: a = MAX, b = 1
        }
    } else {
        /*
         * In this particular case, full range of nd inputs leads
         * to excessively long runtimes, so use 0 or UINT32_MAX instead.
         */
        uint32_t a = (nd_bool()) ? 0 : UINT32_MAX;
        uint32_t b = nd_uint32_t();
        uint32_t r = aws_mul_u32_saturating(a, b);
        if (a > 0 && b > 0 && a > (UINT32_MAX / b)) {
            sassert(r == UINT32_MAX);
        } else {
            // sassert(r == a * b);
            sassert(r == 0); // wrong assertion: expected cex: a = MAX, b = 1, r = MAX
        }
    }
    return 0;
}
