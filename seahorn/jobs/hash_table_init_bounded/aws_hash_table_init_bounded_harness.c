#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>
#include <proof_allocators.h>
#include <seahorn/seahorn.h>
#include <utils.h>

int main(void) {
  /* data structure */
  struct aws_allocator *allocator = sea_can_fail_allocator();
  size_t size = nd_size_t();
  assume(size <= MAX_TABLE_SIZE);
  aws_hash_fn *hash_fn;
  hash_fn = nd_voidp();
  assume(hash_fn);
  aws_hash_callback_eq_fn *equals_fn;
  equals_fn = nd_voidp();
  assume(equals_fn);
  aws_hash_callback_destroy_fn *destroy_key_fn;
  destroy_key_fn = nd_voidp();
  aws_hash_callback_destroy_fn *destroy_value_fn;
  destroy_value_fn = nd_voidp();
  struct aws_hash_table map;
  /* op under verification */
  int rval = aws_hash_table_init(&map, allocator, size, hash_fn, equals_fn,
                                 destroy_key_fn, destroy_value_fn);
  if (rval == AWS_OP_SUCCESS) {
    /* assertions */
    sassert(aws_hash_table_is_valid(&map));
    struct hash_table_state *impl = map.p_impl;
    assert_all_zeroes((uint8_t *)&impl->slots[0],
                      impl->size * sizeof(impl->slots[0]));
  }
}