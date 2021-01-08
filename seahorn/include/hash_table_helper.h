#pragma once

#include <aws/common/hash_table.h>
#include <utils.h>

/*
 * Initialize aws_hash_table with a proper allocated p_impl member
 * and bound param[max_table_entries]
 */
void initialize_bounded_aws_hash_table(struct aws_hash_table *map,
                                       size_t max_table_entries);
void initialize_aws_hash_iter(struct aws_hash_iter *iter,
                              struct aws_hash_table *map);
void mk_valid_aws_hash_iter(struct aws_hash_iter *iter,
                            struct aws_hash_table *map);

void save_byte_from_hash_table(const struct aws_hash_table *map,
                               struct store_byte_from_buffer *storage);

void assert_hash_table_unchanged(const struct aws_hash_table *map,
                                 const struct store_byte_from_buffer *storage);

void uninterpreted_destroy_fn(void *key_or_val);
