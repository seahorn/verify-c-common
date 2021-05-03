#include <linked_list_helper.h>
#include <nondet.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>

// init helper for length <= 2
static inline void init_short_aws_linked_list(struct aws_linked_list *list,
                                              size_t length) {
  struct aws_linked_list_node *front;
  struct aws_linked_list_node *back;
  // initialize
  list->head.prev = NULL;
  list->tail.next = NULL;
  // populate linked list based on nd length
  if (length == 0) {
    aws_linked_list_attach_after(&list->head, &list->tail, true);
  } else if (length == 1) {
    front = malloc(sizeof(struct aws_linked_list_node));
    aws_linked_list_attach_after(&list->head, front, true);
    aws_linked_list_attach_after(front, &list->tail, true);
  } else if (length == 2) {
    front = malloc(sizeof(struct aws_linked_list_node));
    back = malloc(sizeof(struct aws_linked_list_node));
    aws_linked_list_attach_after(&list->head, front, true);
    aws_linked_list_attach_after(front, back, true);
    aws_linked_list_attach_after(back, &list->tail, true);
  }
}

void init_node(struct aws_linked_list_node *node) {
  assume(node);
  node->next = NULL;
  node->prev = NULL;
}

void sea_nd_init_aws_linked_list_from_head(struct aws_linked_list *list,
                                           size_t *length) {
  list->head.prev = NULL;
  list->tail.next = NULL;

  size_t nd_len = nd_size_t();
  *length = nd_len;
  if (nd_len <= 2) {
    init_short_aws_linked_list(list, nd_len);
  } else {
    // HEAD <--> front <--> front_next --> nd ... nd <-- TAIL
    struct aws_linked_list_node *front =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(front);
    struct aws_linked_list_node *front_next =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(front_next);
    aws_linked_list_attach_after(&list->head, front, true);
    aws_linked_list_attach_after(front, front_next, true);
    aws_linked_list_attach_after(front_next, &list->tail, false);
  }
}

void sea_nd_init_aws_linked_list_from_tail(struct aws_linked_list *list,
                                           size_t *length) {
  list->head.prev = NULL;
  list->tail.next = NULL;

  size_t nd_len = nd_size_t();
  *length = nd_len;
  if (nd_len <= 2) {
    init_short_aws_linked_list(list, nd_len);
  } else {
    // HEAD --> nd ... nd <-- back_prev <--> back <--> TAIL
    struct aws_linked_list_node *back =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(back);
    struct aws_linked_list_node *back_prev =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(back_prev);
    aws_linked_list_attach_after(&list->head, back_prev, false);
    aws_linked_list_attach_after(back_prev, back, true);
    aws_linked_list_attach_after(back, &list->tail, true);
  }
}

void sea_nd_init_aws_linked_list(struct aws_linked_list *list,
                                 size_t *length) {
  list->head.prev = NULL;
  list->tail.next = NULL;

  size_t nd_len = nd_size_t();
  *length = nd_len;
  if (nd_len <= 2) {
    init_short_aws_linked_list(list, nd_len);
  }
  else {
    // HEAD <--> front --> nd ... nd <-- back <--> TAIL
    struct aws_linked_list_node *front =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(front);
    struct aws_linked_list_node *back =
        malloc(sizeof(struct aws_linked_list_node));
    init_node(back);
    aws_linked_list_attach_after(&list->head, front, true);
    aws_linked_list_attach_after(front, back, false);
    aws_linked_list_attach_after(back, &list->tail, true);
  }
}

bool nodes_prev_equal(struct aws_linked_list_node *node,
                      struct saved_aws_linked_list_node *saved) {
  return node == saved->node && node->prev == saved->node_prev;
}

bool nodes_next_equal(struct aws_linked_list_node *node,
                      struct saved_aws_linked_list_node *saved) {
  return node == saved->node && node->next == saved->node_next;
}

bool nodes_equal(struct aws_linked_list_node *node,
                 struct saved_aws_linked_list_node *saved) {
  return nodes_prev_equal(node, saved) && nodes_next_equal(node, saved);
}

void sea_save_aws_node_to_sea_node(struct aws_linked_list_node *s,
                                   struct saved_aws_linked_list_node *d) {
  d->node = s;
  d->node_prev = s->prev;
  d->node_next = s->next;
}

bool check_tail_unchanged(struct aws_linked_list *list,
                          struct saved_aws_linked_list *saved) {
  return nodes_equal(&list->tail, &saved->tail);
}

bool is_aws_list_unchanged_to_tail(struct aws_linked_list *list,
                                   struct saved_aws_linked_list *saved) {
  if (saved->saved_size == 0) {
    // if saved size is zero, only check that tail is unchanged
    return nodes_next_equal(&list->tail, &saved->tail);
  } else if (saved->saved_size == 1) {
    // if saved size is 1 then check start and tail are unchanged
    return nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(&list->tail, &saved->tail);

  } else if (saved->saved_size == 2) {
    // if saved size is 2 then check start, start.next and tail are unchanged
    return nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(saved->save_point->next, &saved->nodes[1]) &&
           nodes_equal(&list->tail, &saved->tail);

  } else if (saved->saved_size == 3) {
    // we only save a maximum of three nodes since that is the maximum we
    // construct concretely are head <--> node1 <--> node2
    return nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(saved->save_point->next, &saved->nodes[1]) &&
           nodes_equal(saved->save_point->next->next, &saved->nodes[2]) &&
           nodes_equal(&list->tail, &saved->tail);
  } else {
    return false;
  }
  // do nothing here: if condition should be exhaustive
}

bool is_aws_list_unchanged_to_head(struct aws_linked_list *list,
                                   struct saved_aws_linked_list *saved) {
  if (saved->saved_size == 0) {
    // if saved size is zero, only check that head is unchanged
    return nodes_prev_equal(&list->head, &saved->head);
  } else if (saved->saved_size == 1) {
    // if saved size is 1 then check start and head are unchanged
    return nodes_prev_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(&list->head, &saved->head);
    ;
  } else if (saved->saved_size == 2) {
    // if saved size is 2 then check start, start.prev and head are unchanged
    return nodes_prev_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(saved->save_point->prev, &saved->nodes[1]) &&
           nodes_equal(&list->head, &saved->head);
    ;
  } else if (saved->saved_size == 3) {
    // we only save a maximum of three nodes since that is the maximum we
    // construct concretely are node1 <--> node2 <--> tail
    return nodes_prev_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(saved->save_point->prev, &saved->nodes[1]) &&
           nodes_equal(saved->save_point->prev->prev, &saved->nodes[2]) &&
           nodes_equal(&list->head, &saved->head);
  } else {
    return false;
  }
  // do nothing here: if condition should be exhaustive
}

bool is_aws_list_unchanged_full(struct aws_linked_list *list,
                                   struct saved_aws_linked_list *saved) {
  if (saved->saved_size == 0)
  { /* saved zero nodes */
    return saved->head.node_next == saved->tail.node &&
           saved->tail.node_prev == saved->head.node;
  }
  else if (saved->saved_size == 1)
  {
    // when content consists of one node, only check equality of the node itself
    return saved->save_point == saved->save_point_end &&
           saved->save_point == saved->nodes[0].node;
  }
  else if (saved->saved_size == 2)
  {
    return nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_prev_equal(saved->save_point_end, &saved->nodes[1]);
  }
  else if (saved->saved_size == 3)
  {
    if (nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
        nodes_prev_equal(saved->save_point_end, &saved->nodes[2]))
    {
      if (saved->nodes[1].node == saved->save_point->next)
      {
        return nodes_equal(saved->save_point->next, &saved->nodes[1]);
      }
      else if (saved->nodes[1].node == saved->save_point_end->prev)
      {
        return nodes_equal(saved->save_point_end->prev, &saved->nodes[1]);
      }
      else
        return false;
    }
    else
      return false;
  }
  else if (saved->saved_size == 4)
  {
    return nodes_next_equal(saved->save_point, &saved->nodes[0]) &&
           nodes_equal(saved->save_point->next, &saved->nodes[1]) &&
           nodes_equal(saved->save_point_end->prev, &saved->nodes[2]) &&
           nodes_prev_equal(saved->save_point_end, &saved->nodes[3]);
  }
  else
    return false;
}

// iterator function for save*Node
struct aws_linked_list_node *getNext(struct aws_linked_list_node *node) {
  return node->next;
}

// iterator function for save*Node
struct aws_linked_list_node *getPrev(struct aws_linked_list_node *node) {
  return node->prev;
}

void save_one_node(struct aws_linked_list_node *start,
                   struct saved_aws_linked_list *to_save) {
  sea_save_aws_node_to_sea_node(start, &to_save->nodes[0]);
  to_save->saved_size = 1;
}
void save_two_nodes(
    struct aws_linked_list_node *start, struct saved_aws_linked_list *to_save,
    struct aws_linked_list_node *(*next)(struct aws_linked_list_node *)) {
  sea_save_aws_node_to_sea_node(start, &to_save->nodes[0]);
  sea_save_aws_node_to_sea_node((*next)(start), &to_save->nodes[1]);
  to_save->saved_size = 2;
}
void save_three_nodes(
    struct aws_linked_list_node *start, struct saved_aws_linked_list *to_save,
    struct aws_linked_list_node *(*next)(struct aws_linked_list_node *)) {
  sea_save_aws_node_to_sea_node(start, &to_save->nodes[0]);
  sea_save_aws_node_to_sea_node((*next)(start), &to_save->nodes[1]);
  sea_save_aws_node_to_sea_node((*next)((*next)(start)), &to_save->nodes[2]);
  to_save->saved_size = 3;
}
void aws_linked_list_save_to_tail(struct aws_linked_list *list, size_t size,
                                  struct aws_linked_list_node *start,
                                  struct saved_aws_linked_list *to_save) {
  sea_save_aws_node_to_sea_node(&list->head, &to_save->head);
  sea_save_aws_node_to_sea_node(&list->tail, &to_save->tail);

  to_save->save_point = start;

  if (size == 0) {
    // only possibility is to save head or tail.
    // Note tail is never saved in nodes[..] array
    if (&list->head == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  } else if (size == 1) {
    // either save head, head.next or only head.next
    if (&list->head == start) {
      save_two_nodes(start, to_save, getNext);
    } else if (list->head.next == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  } else if (size > 1) {
    // either save
    // 1) head, head.next, head.next.next OR
    // 2) head.next, head.next.next OR
    // 3) head.next.next
    if (&list->head == start) {
      save_three_nodes(start, to_save, getNext);
    } else if (list->head.next == start) {
      save_two_nodes(start, to_save, getNext);
    } else if (list->head.next->next == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  }
}

void aws_linked_list_save_to_head(struct aws_linked_list *list, size_t size,
                                  struct aws_linked_list_node *start,
                                  struct saved_aws_linked_list *to_save) {
  sea_save_aws_node_to_sea_node(&list->head, &to_save->head);
  sea_save_aws_node_to_sea_node(&list->tail, &to_save->tail);

  to_save->save_point = start;

  if (size == 0) {
    // only possibility is to save tail or head
    // Note: head is never saved in nodes[..] array
    if (&list->tail == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  } else if (size == 1) {
    // either save (in-order) tail, tail.prev or only tail.prev
    if (&list->tail == start) {
      save_two_nodes(start, to_save, getPrev);
    } else if (list->tail.prev == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  } else if (size > 1) {
    // either save (in-order)
    // 1) tail, tail.prev, tail.prev.prev OR
    // 2) tail.prev, tail.prev.prev OR
    // 3) tail.prev.prev
    if (&list->tail == start) {
      save_three_nodes(start, to_save, getPrev);
    } else if (list->tail.prev == start) {
      save_two_nodes(start, to_save, getPrev);
    } else if (list->tail.prev->prev == start) {
      save_one_node(start, to_save);
    } else {
      to_save->saved_size = 0;
    }
  }
}

void aws_linked_list_save_full(struct aws_linked_list *list, size_t size,
                               struct aws_linked_list_node *start,
                               struct aws_linked_list_node *end,
                               struct saved_aws_linked_list *to_save)
{
  sea_save_aws_node_to_sea_node(&list->head, &to_save->head);
  sea_save_aws_node_to_sea_node(&list->tail, &to_save->tail);
  to_save->save_point = start;
  to_save->save_point_end = end;
  if (start == end) {
    save_one_node(start, to_save);
    return;
  }
  if (size == 0) {
    /* only save head and tail */
    if (start == &list->head) {
      save_two_nodes(start, to_save, getNext);
    } else {
      /* save content when empty */
      to_save->saved_size = 0;
    }
  } else if (size == 1) {
    /* front nodes: [head, head.next...] or [head.next...] */
    /* back nodes: [...tail] or same as front nodes */
    size_t back_nodes_start = 0;
    if (start == &list->head) {
      sea_save_aws_node_to_sea_node(&list->head, &to_save->nodes[0]);
      sea_save_aws_node_to_sea_node(list->head.next, &to_save->nodes[1]);
      to_save->saved_size = 2;
      back_nodes_start = 2;
    } else if (start == list->head.next) {
      sea_save_aws_node_to_sea_node(list->head.next, &to_save->nodes[0]);
      to_save->saved_size = 1;
      back_nodes_start = 1;
    }
    /* head.next == tail.prev, so only conditionally add tail */
    if (end == &list->tail) {
      sea_save_aws_node_to_sea_node(end, &to_save->nodes[back_nodes_start]);
      to_save->saved_size += 1;
    }
  } else if (size > 1) {
    size_t back_nodes_start = 0;
    /* front nodes: [head, head.next...] or [head.next...] */
    /* back nodes: [...tail.prev] or [...tail.prev, tail] */
    if (start == &list->head) {
      sea_save_aws_node_to_sea_node(&list->head, &to_save->nodes[0]);
      sea_save_aws_node_to_sea_node(list->head.next, &to_save->nodes[1]);
      to_save->saved_size = 2;
      back_nodes_start = 2;
    } else if (start == list->head.next) {
      sea_save_aws_node_to_sea_node(list->head.next, &to_save->nodes[0]);
      to_save->saved_size = 1;
      back_nodes_start = 1;
    }
    if (end == &list->tail) {
      sea_save_aws_node_to_sea_node(list->tail.prev, &to_save->nodes[back_nodes_start]);
      sea_save_aws_node_to_sea_node(&list->tail, &to_save->nodes[back_nodes_start + 1]);
      to_save->saved_size += 2;
    } else if (end == list->tail.prev) {
      sea_save_aws_node_to_sea_node(list->tail.prev, &to_save->nodes[back_nodes_start]);
      to_save->saved_size += 1;
    }
  }
}

void aws_linked_list_attach_after(struct aws_linked_list_node *after,
                                  struct aws_linked_list_node *to_attach,
                                  bool directly_attached) {
  if (directly_attached) {
    after->next = to_attach;
    to_attach->prev = after;
  } else {
    after->next = nd_linked_list_node();
    assume(after->next != NULL);
    to_attach->prev = nd_linked_list_node();
    assume(to_attach->prev != NULL);
  }
}

bool is_aws_linked_list_node_attached_after(
    struct aws_linked_list_node *after,
    struct aws_linked_list_node *to_attach) {
  return after->next == to_attach && to_attach->prev == after;
}
