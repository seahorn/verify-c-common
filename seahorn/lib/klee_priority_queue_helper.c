#include <array_list_helper.h>
#include <nondet.h>
#include <priority_queue_helper.h>

int nd_aws_priority_queue_compare_fn(const void *a, const void *b) { return nd_int(); }

void initialize_priority_queue(struct aws_priority_queue *queue) {
  queue->pred = nd_aws_priority_queue_compare_fn;
  initialize_bounded_array_list(&queue->container);
  initialize_bounded_array_list(&queue->backpointers);
}

bool aws_priority_queue_is_bounded(struct aws_priority_queue *queue,
                                   const size_t max_initial_item_allocation,
                                   const size_t max_item_size) {
  bool b1 = aws_array_list_is_bounded(&queue->container, max_initial_item_allocation,
                                      max_item_size);
  bool b2 = aws_array_list_is_bounded(&queue->backpointers, max_initial_item_allocation,
                                      sizeof(struct aws_priority_queue_node *));
  return b1 && b2;
}
