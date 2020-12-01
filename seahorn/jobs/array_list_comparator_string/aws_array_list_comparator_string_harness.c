/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/array_list.h>
#include <array_list_helper.h>
#include <string_helper.h>
#include <utils.h>

extern void sea_dsa_alias(const void *p, ...);

int main() {
    struct aws_string *str_a = ensure_string_is_allocated_bounded_length(MAX_BUFFER_SIZE);
    struct aws_string *str_b = nd_bool() ? str_a : ensure_string_is_allocated_bounded_length(MAX_BUFFER_SIZE);

    bool nondet_parameter_a = nd_bool();
    bool nondet_parameter_b = nd_bool();
    if (aws_array_list_comparator_string(nondet_parameter_a ? &str_a : NULL, nondet_parameter_b ? &str_b : NULL) == 0) {
        if (nondet_parameter_a && nondet_parameter_b) {
            assert_bytes_match(str_a->bytes, str_b->bytes, str_a->len);
        }
    }

    return 0;
}
