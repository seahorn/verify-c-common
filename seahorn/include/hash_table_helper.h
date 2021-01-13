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

void ensure_hash_table_has_valid_destroy_functions(struct aws_hash_table *map);

bool aws_hash_table_has_an_empty_slot(const struct aws_hash_table *const map,
                                      size_t *const rval);

void hash_proof_destroy_noop(void *p);

/* XXX: EXPENSIVE! Iterates through hash_table_state->slots and counts
    number of entries with hash_code != 0 */
size_t aws_hash_table_deep_entry_count(const struct aws_hash_table *const map);

/* returns true if map->p_impl->entry_count matches aws_hash_table_deep_entry_count(map) */
bool aws_hash_table_entry_count_is_valid(const struct aws_hash_table *const map);

/* returns true if hash_code of all entries are 0 */
bool aws_hash_table_deep_is_empty(const struct aws_hash_table *const map);
