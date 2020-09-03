/*
 */

#include <aws/common/hash_table.h>

#include <seahorn/seahorn.h>
#include <nondet.h>

int main() {
    void *p1 = nd_voidp();
    void *p2 = nd_voidp();
    bool rval = aws_ptr_eq(p1, p2);
    sassert(rval == (p1 == p2));
    return 0;
}
