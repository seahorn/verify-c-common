/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include <aws/common/common.h>
#include <proof_helpers/nondet.h>
#include <stdlib.h>

/**
 *
 */
#define OBJECT_BITS 8
#define MAX_MALLOC (SIZE_MAX >> (OBJECT_BITS + 1))

#define MEM_BLOCK 4096

void *realloc( void *ptr, size_t new_size );

/**
 *
 */
void *bounded_calloc(size_t num, size_t size);

/**
 *
 */
void *bounded_malloc(size_t size);

/**
 *
 */
struct aws_allocator *_allocator(void);
