/*
 *
 */

#include <aws/common/linked_list.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main() {
  /* data structure */
  struct aws_linked_list_node node; // Preconditions require node to not be NULL

  /* perform operation under verification */
  aws_linked_list_node_reset(&node);

  /* assertions */
  assert_all_zeroes((const uint8_t *)&node,
                    sizeof(struct aws_linked_list_node));
}
