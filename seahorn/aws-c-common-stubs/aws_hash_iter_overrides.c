#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <utils.h>

/**
 * Functions:
 * aws_hash_iter_begin, aws_hash_iter_done, aws_hash_iter_next and
 * aws_hash_iter_delete Replaces loop mechanisms with non-determinism
 */

struct aws_hash_iter aws_hash_iter_begin(const struct aws_hash_table *map) {
  /* Leave it as non-det as possible */
  AWS_PRECONDITION(aws_hash_table_is_valid(map));

  /* Build a nondet iterator, set the required fields, and return it */
  struct aws_hash_iter rval;
  rval.map = map;
  rval.limit = map->p_impl->size;
  rval.slot = nd_size_t();
  assume(rval.slot <= rval.limit);
  rval.status = (rval.slot == rval.limit) ? AWS_HASH_ITER_STATUS_DONE
                                          : AWS_HASH_ITER_STATUS_READY_FOR_USE;
  return rval;
}

bool aws_hash_iter_done(const struct aws_hash_iter *iter) {
  AWS_PRECONDITION(iter->status == AWS_HASH_ITER_STATUS_DONE ||
                       iter->status == AWS_HASH_ITER_STATUS_READY_FOR_USE,
                   "Input aws_hash_iter [iter] status should either be done or "
                   "ready to use.");
  bool rval = iter->slot == iter->limit;
  sassert(rval == (iter->status == AWS_HASH_ITER_STATUS_DONE));
  return rval;
}

void aws_hash_iter_next(struct aws_hash_iter *iter) {
  if (iter->slot == iter->limit) {
    iter->status = AWS_HASH_ITER_STATUS_DONE;
    return;
  }

  /* Build a nondet iterator, set the required fields, and copy it over */
  struct aws_hash_iter rval;
  rval.map = iter->map;
  rval.limit = iter->limit;
  size_t next_step = nd_size_t();
  assume(next_step > 0 && next_step <= iter->limit - iter->slot);
  rval.limit = iter->limit;
  rval.slot = iter->slot + next_step;
  rval.status = (rval.slot == rval.limit) ? AWS_HASH_ITER_STATUS_DONE
                                          : AWS_HASH_ITER_STATUS_READY_FOR_USE;
  *iter = rval;
}

/* delete always leaves the element unusable, so we'll just leave the element
 * totally nondet */
/* Seahorn: post-condition of aws_hash_iter_delete should also include
   iter->map->state->entry_count -= 1 */
void aws_hash_iter_delete(struct aws_hash_iter *iter, bool destroy_contents) {
  /* Build a nondet iterator, set the required fields, and copy it over */
  struct aws_hash_iter rval;
  rval.map = iter->map;
  rval.slot = iter->slot;
  rval.limit = iter->limit - 1;
  rval.status = AWS_HASH_ITER_STATUS_DELETE_CALLED;
  rval.map->p_impl->entry_count--;
  *iter = rval;
}