#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <utils.h>

int main(void) {
  /* data structure */
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  assume(aws_hash_table_is_valid(&map));

  size_t empty_slot_idx;
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));

  struct store_byte_from_buffer old_byte;
  save_byte_from_hash_table(&map, &old_byte);

  void *key = nd_voidp();
  struct aws_hash_element elem;
  struct aws_hash_element *p_elem = &elem;

  /* Preconditions */
  assume(aws_hash_table_is_valid(&map));
  assume(AWS_OBJECT_PTR_IS_WRITABLE(&p_elem));

  int rval = aws_hash_table_find(&map, key, &p_elem);
  sassert(rval == AWS_OP_SUCCESS);
  if (p_elem) {
    sassert(AWS_OBJECT_PTR_IS_READABLE(p_elem));
#ifdef __SEA_UNINTERP_FN__
    sassert(p_elem->key == key || uninterpreted_equals(p_elem->key, key));
#endif
  }
  sassert(aws_hash_table_is_valid(&map));
  assert_hash_table_unchanged(&map, &old_byte);
  return 0;
}