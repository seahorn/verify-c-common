/**
 * FUNCTION: s_update_template_size
 *
 * This function overrides the original implementation of the
 * s_update_template_size function from hash_table.c by replacing floating
 * point multiplication with nd_size_t;
 * template->max_load should always be less than template->size,
 * so stubbing multiplication result with nondet value is safe
 * alternatively we can add support for fmul semantic in seahorn
 */

#include <aws/common/hash_table.h>
#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>
#include <nondet.h>
#include <seahorn/seahorn.h>

#include <stdlib.h>

int s_update_template_size(struct hash_table_state *template,
                           size_t expected_elements) {
  size_t min_size = expected_elements;

  if (min_size < 2) {
    min_size = 2;
  }

  /* size is always a power of 2 */
  size_t size;
  if (aws_round_up_to_power_of_two(min_size, &size)) {
    return AWS_OP_ERR;
  }

  /* Update the template once we've calculated everything successfully */
  template->size = size;
  /* original code: */
  // template->max_load = (size_t)(template->max_load_factor *
  // (double)template->size);
  template->max_load = nd_size_t();
  // if size > 0 then max_load > 0
  assume(size <= 0 || template->max_load > 0);
  assume(template->max_load >= template->entry_count);
  /* Ensure that there is always at least one empty slot in the hash table */
  if (template->max_load >= size) {
    template->max_load = size - 1;
  }

  /* Since size is a power of 2: (index & (size - 1)) == (index % size) */
  template->mask = size - 1;

  return AWS_OP_SUCCESS;
}