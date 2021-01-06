/*
 *
 */

#pragma once

#include <aws/common/common.h>
#include <nondet.h>
#include <stdlib.h>

/**
 *
 */
#define OBJECT_BITS 8
#define MAX_MALLOC (SIZE_MAX >> (OBJECT_BITS + 1))

#define MEM_BLOCK 4096

void *realloc(void *ptr, size_t new_size);

/**
 *
 */
void *can_fail_calloc(size_t num, size_t size);

void *bounded_calloc(size_t num, size_t size);

/**
 *
 */
void *bounded_malloc(size_t size);
void *bounded_malloc_pure(size_t size);
void *can_fail_malloc(size_t size);

/**
 * Pointer to SeaHorn-based allocator
 */
struct aws_allocator *sea_allocator(void);

/* allocator where malloc, free and calloc can non-det fail (return NULL)*/
struct aws_allocator *sea_can_fail_allocator(void);