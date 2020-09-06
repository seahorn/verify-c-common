/*
 */

#include <aws/common/math.h>

#include <seahorn/seahorn.h>
#include <nondet.h>

int main() {
    size_t test_val = nd_size_t();
    bool rval = aws_is_power_of_two(test_val);
#if ULONG_MAX == SIZE_MAX
    int popcount = __builtin_popcountl(test_val);
#elif ULLONG_MAX == SIZE_MAX
    int popcount = __builtin_popcountll(test_val);
#else
#    error
#endif
    sassert(rval != (popcount == 1));
    return 0;
}
