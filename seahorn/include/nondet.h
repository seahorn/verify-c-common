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
 * Non-determinstic functions 
 */
extern bool nd_bool(void);
extern int nd_int(void);
extern size_t nd_size_t(void);
extern uint16_t nd_uint16_t(void);
extern uint32_t nd_uint32_t(void);
extern uint64_t nd_uint64_t(void);
extern uint8_t nd_uint8_t(void);
extern void *nd_voidp(void);

/* store allocated mem size */
extern int nd_store_mem_size(void);
