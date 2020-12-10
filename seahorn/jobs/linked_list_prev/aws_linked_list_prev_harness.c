#include "seahorn/seahorn.h"
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>

int main(void) {
  /* data structure */
  struct aws_linked_list_node node; // Preconditions require node to not be NULL
  struct aws_linked_list_node
      before; // Preconditions require before to not be NULL

  /* Assume the preconditions */
  aws_linked_list_attach_after(&before, &node, true);

  /* perform operation under verification */
  struct aws_linked_list_node *rval = aws_linked_list_prev(&node);

  /* assertions */
  sassert(aws_linked_list_node_prev_is_valid(&node));
  sassert(aws_linked_list_node_next_is_valid(rval));
  sassert(rval == &before);
}
