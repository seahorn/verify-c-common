/*
 *
 */

#pragma once

#include <aws/common/common.h>
#include <nondet.h>
#include <stdlib.h>

#define OBJECT_BITS 8
#define MAX_MALLOC (SIZE_MAX >> (OBJECT_BITS + 1))

#define MEM_BLOCK 4096

void *realloc(void *ptr, size_t new_size);

/**
 * Deterministically allocates [size] bytes and returns a pointer;
 * memory allocated will be marked as containing non-det content using memhavoc
 */
void *bounded_malloc(size_t size);

/**
 * Can non-deterministically fail;
 * if successful, allocate [size] bytes and returns a pointer;
 * memory allocated will be marked as containing non-det content using memhavoc
 */
void *can_fail_malloc(size_t size);

/**
 * Pointer to SeaHorn-based allocator
 */
struct aws_allocator *sea_allocator(void);
