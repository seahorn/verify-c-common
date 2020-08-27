/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may not use
 * this file except in compliance with the License. A copy of the License is
 * located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Mark nondet functions as not accessing memory
 * Note: if the attribute is too agressive, the optimizer might remove
 *       calls to nondet functions, thus reducing the amount of non-determinism.
 * Note: using each nondet function only once grately simplifies debugging.
 */
#define NONDET_FN_ATTR __declspec(noalias)

/**
 * Non-determinstic functions 
 */
extern NONDET_FN_ATTR bool nd_bool(void);
extern NONDET_FN_ATTR int nd_int(void);
extern NONDET_FN_ATTR size_t nd_size_t(void); 
extern NONDET_FN_ATTR uint16_t nd_uint16_t(void);
extern NONDET_FN_ATTR uint32_t nd_uint32_t(void);
extern NONDET_FN_ATTR uint64_t nd_uint64_t(void);
extern NONDET_FN_ATTR uint8_t nd_uint8_t(void);
extern void *nd_voidp(void) __attribute__((malloc));

/* store allocated mem size */
extern NONDET_FN_ATTR int nd_store_mem_size(void);
