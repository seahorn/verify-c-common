/*
 */

#include <aws/common/math.h>
#include <seahorn/seahorn.h>
#include <nondet.h>

int main() {
    size_t test_val = nd_size_t();
    assume(test_val <= 2);
    size_t result;
    int rval = aws_round_up_to_power_of_two(test_val, &result);

#if ULONG_MAX == SIZE_MAX
    int popcount = __builtin_popcountl(result);
#elif ULLONG_MAX == SIZE_MAX
    int popcount = __builtin_popcountll(result);
#else
#    error
#endif
    if (rval == AWS_OP_SUCCESS) {
        sassert(popcount == 1);
        sassert(test_val <= result);
        sassert(test_val >= result >> 1);
    } else {
        // Only fail if rounding up would cause us to overflow.
        sassert(test_val > ((SIZE_MAX >> 1) + 1));
    }
    return 0;
}
