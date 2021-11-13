#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

#include <seahorn/seahorn.h>

#include <config.h>
#include <hash_table_helper.h>
#include <utils.h>

int main(void) {
  /* parameters */
  struct aws_hash_table map;
  initialize_bounded_aws_hash_table(&map, MAX_TABLE_SIZE);
  size_t empty_slot_idx;
  void *key = nd_voidp();
  struct aws_hash_element elem;
  struct aws_hash_element *p_elem = &elem;

  /* assumptions */
  assume(aws_hash_table_is_valid(&map));
  assume(aws_hash_table_has_an_empty_slot(&map, &empty_slot_idx));

  /* save current state of the data structure */
  sea_tracking_on();
  sea_reset_modified((char *)&map);
  sea_reset_modified((char *)map.p_impl);

  /* Preconditions */
  assume(aws_hash_table_is_valid(&map));
  assume(AWS_OBJECT_PTR_IS_WRITABLE(&p_elem));

  /* operation under verification */
  int rval = aws_hash_table_find(&map, key, &p_elem);
  
  /* assertions */
  sassert(rval == AWS_OP_SUCCESS);
  if (p_elem) {
    sassert(AWS_OBJECT_PTR_IS_READABLE(p_elem));
#ifdef __SEA_UNINTERP_FN__
    sassert(p_elem->key == key || uninterpreted_equals(p_elem->key, key));
#endif
  }
  sassert(aws_hash_table_is_valid(&map));
  sassert(!sea_is_modified((char *)&map));
  sassert(!sea_is_modified((char *)map.p_impl));
  return 0;
}
