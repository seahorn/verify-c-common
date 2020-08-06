/*
 * 
 */

#pragma once

#include <aws/common/array_list.h>
#include <aws/common/byte_buf.h>
#include <nondet.h>
#include <stddef.h>
#include <stdint.h>

#define IMPLIES(a, b) (!(a) || (b))

struct store_byte_from_buffer {
    size_t index;
    uint8_t byte;
};

/**
 * Asserts whether all bytes from two arrays of same length match.
 */
void assert_bytes_match(
    const uint8_t *const a, 
    const uint8_t *const b, 
    const size_t len);

/**
 * Asserts whether all bytes from an array are equal to c.
 */
void assert_all_bytes_are(
    const uint8_t *const a, 
    const uint8_t c, 
    const size_t len);

/**
 * Asserts whether all bytes from an array are equal to 0.
 */
void assert_all_zeroes(const uint8_t *const a, const size_t len);

/**
 * Asserts whether the byte in storage correspond to the byte in the same 
 * position in buffer.
 */
void assert_byte_from_buffer_matches(
    const uint8_t *const buffer, 
    const struct store_byte_from_buffer *const b);

/**
 * Nondeterministically selects a byte from array and stores it into a 
 * store_array_list_byte structure. Afterwards, one can prove using the 
 * assert_array_list_equivalence function whether no byte in the array has 
 * changed.
 */
void save_byte_from_array(
    const uint8_t *const array, 
    const size_t size, 
    struct store_byte_from_buffer *const storage);

/**
 * Asserts two aws_array_list structures are equivalent. Prior to using this 
 * function, it is necessary to select a non-deterministic byte from the rhs 
 * aws_array_list structure (use save_byte_from_array function), so it can 
 * properly assert all bytes match.
 */
void assert_array_list_equivalence(
    const struct aws_array_list *const lhs,
    const struct aws_array_list *const rhs,
    const struct store_byte_from_buffer *const rhs_byte);

void assert_byte_buf_equivalence(
    const struct aws_byte_buf *const lhs,
    const struct aws_byte_buf *const rhs,
    const struct store_byte_from_buffer *const rhs_byte);

void assert_byte_cursor_equivalence(
    const struct aws_byte_cursor *const lhs,
    const struct aws_byte_cursor *const rhs,
    const struct store_byte_from_buffer *const rhs_byte);
/**
 * Standard stub function to compare two items.
 */
int nondet_compare(const void *const a, const void *const b);

/**
 * Standard stub function to compare two items.
 */
int uninterpreted_compare(const void *const a, const void *const b);

/**
 * Standard stub function to compare two items.
 */
bool nondet_equals(const void *const a, const void *const b);

/**
 * Standard stub function to compare two items.
 * Also enforces uninterpreted_hasher() to be equal for equal values.
 */
bool uninterpreted_equals(const void *const a, const void *const b);

/**
 * uninterpreted_equals(), but with an extra assertion that a and b are both 
 * not null
 */
bool uninterpreted_equals_assert_inputs_nonnull(
    const void *const a, 
    const void *const b);

/**
 * Standard stub function to hash one item.
 */
uint64_t nondet_hasher(const void *a);

/**
 * Standard stub function to hash one item.
 */
uint64_t uninterpreted_hasher(const void *a);

/**
 * Standard stub function of a predicate
 */
bool uninterpreted_predicate_fn(uint8_t value);

unsigned sea_strlen(const char *str);

const char *ensure_c_str_is_allocated(size_t max_size);

bool aws_byte_cursor_is_bounded(
    const struct aws_byte_cursor *const cursor, 
    const size_t max_size);
    
void ensure_byte_buf_has_allocated_buffer_member(
    struct aws_byte_buf *const buf);
