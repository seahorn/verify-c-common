#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <proof_allocators.h>
#include <utils.h>

int main(void) {
  /* data structure */
  struct aws_allocator *allocator = sea_allocator();
  size_t size = nd_size_t();
  /* no upbound for size of hash_table */
  aws_hash_fn *hash_fn;
  hash_fn = uninterpreted_hasher;
  assume(hash_fn);
  aws_hash_callback_eq_fn *equals_fn;
  equals_fn = uninterpreted_equals;
  assume(equals_fn);
  aws_hash_callback_destroy_fn *destroy_key_fn;
  destroy_key_fn = uninterpreted_destroy_fn;
  aws_hash_callback_destroy_fn *destroy_value_fn;
  destroy_value_fn = uninterpreted_destroy_fn;
  struct aws_hash_table map;
  /* op under verification */
  int rval = aws_hash_table_init(&map, allocator, size, hash_fn, equals_fn,
                                 destroy_key_fn, destroy_value_fn);
  if (rval == AWS_OP_SUCCESS) {
    /* assertions */
    sassert(aws_hash_table_is_valid(&map));
  }
  return 0;
}
