/*
 *
 */

#pragma once

#include <aws/common/array_list.h>

void initialize_array_list(struct aws_array_list *const list);

/*
 * Initialize a bounded array list by given a max_initial_size
 */
void initialize_bounded_array_list(struct aws_array_list *const list);

/*
 * Checks whether aws_array_list is bounded by max_initial_item_allocation and max_item_size
 */
bool aws_array_list_is_bounded(
    const struct aws_array_list *const list,
    const size_t max_initial_item_allocation,
    const size_t max_item_size);

/**
 * Ensures the data member of an aws_array_list structure is correctly allocated
 */
void ensure_array_list_has_allocated_data_member(struct aws_array_list *const list);
