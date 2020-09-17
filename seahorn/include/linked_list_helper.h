#pragma once

#include <aws/common/linked_list.h>

#include <stddef.h>

void ensure_linked_list_is_allocated(struct aws_linked_list *const list, size_t max_length, size_t *length);
bool sea_aws_linked_list_is_valid(const struct aws_linked_list *list, size_t length);

