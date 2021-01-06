#pragma once

#include <aws/common/hash_table.h>
#include <aws/common/private/hash_table_impl.h>

/*
 * Ensures aws_hash_table has a proper allocated p_impl member
 */
void ensure_allocated_hash_table(struct aws_hash_table *map,
                                 size_t max_table_entries);
