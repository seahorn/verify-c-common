#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>

int main(void) {
  /* data structure */
  struct aws_linked_list list;

  /* Note: list is assumed to be a valid pointer in the function's
   *       precondition */

  /* perform operation under verification */
  aws_linked_list_init(&list);

  /* assertions */
  sassert(aws_linked_list_is_valid(&list));

  return 0;
}