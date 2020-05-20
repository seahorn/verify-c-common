/*
 * Copyright 2010-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#include <aws/common/array_list.h>
#include <aws/common/private/array_list.h>

#include <stdlib.h> /* qsort */

int aws_array_list_copy(const struct aws_array_list *AWS_RESTRICT from, struct aws_array_list *AWS_RESTRICT to) {
    AWS_FATAL_PRECONDITION(from->item_size == to->item_size);
    AWS_FATAL_PRECONDITION(from->data);
    AWS_PRECONDITION(aws_array_list_is_valid(from));
    AWS_PRECONDITION(aws_array_list_is_valid(to));

    size_t copy_size = 0;
    if (aws_mul_size_checked(from->length, from->item_size, &copy_size)) {
        AWS_POSTCONDITION(aws_array_list_is_valid(from));
        AWS_POSTCONDITION(aws_array_list_is_valid(to));
        return AWS_OP_ERR;
    }

    if (to->current_size >= copy_size) {
        if (copy_size > 0) {
            memcpy(to->data, from->data, copy_size);
        }
        to->length = from->length;
        AWS_POSTCONDITION(aws_array_list_is_valid(from));
        AWS_POSTCONDITION(aws_array_list_is_valid(to));
        return AWS_OP_SUCCESS;
    }
    /* if to is in dynamic mode, we can just reallocate it and copy */

    if (to->alloc != NULL) {
        void *tmp = aws_mem_acquire(to->alloc, copy_size);

        if (!tmp) {
            AWS_POSTCONDITION(aws_array_list_is_valid(from));
            AWS_POSTCONDITION(aws_array_list_is_valid(to));
            return AWS_OP_ERR;
        }

        memcpy(tmp, from->data, copy_size);
        if (to->data) {
            aws_mem_release(to->alloc, to->data);
        }

        to->data = tmp;
        to->length = from->length;
        to->current_size = copy_size;
        AWS_POSTCONDITION(aws_array_list_is_valid(from));
        AWS_POSTCONDITION(aws_array_list_is_valid(to));
        return AWS_OP_SUCCESS;
    }

    return aws_raise_error(AWS_ERROR_DEST_COPY_TOO_SMALL);
}
