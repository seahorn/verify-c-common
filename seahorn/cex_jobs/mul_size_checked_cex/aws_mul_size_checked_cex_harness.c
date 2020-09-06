#include <aws/common/math.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

/**
 */
int main() {
    if (nd_bool()) {
        /*
         */
	// AG: seahorn can deal with arbitrary integers
        // AG: CBMC was limited to testing with exactly two inputs!
        uint64_t a = nd_uint64_t();
        uint64_t b = nd_uint64_t();
        uint64_t r = nd_uint64_t();
        if (aws_mul_u64_checked(a, b, &r)) {
            sassert(r == a * b);
        } else {
            // AG: the assert is wrong. it is taken from add_size_checked
            // sassert((b > 0) && (a > (UINT64_MAX - b)));
            sassert(b > 0);
        }
    } else {
        /*
         */
        // AG: seahorn can deal with arbitrary integers
        // AG: CBMC was limited to testing with exactly two inputs!
        uint32_t a = nd_uint32_t();
        uint32_t b = nd_uint32_t();
        uint32_t r = nd_uint32_t();
        if (!aws_mul_u32_checked(a, b, &r)) {
            sassert(r == a * b);
        } else {
            // AG: the assert is wrong. it is taken from add_size_checked
            // sassert((b > 0) && (a > (UINT32_MAX - b)));
            sassert(b > 0);
        }
    }
    return 0;
}
