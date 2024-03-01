#include <aws/common/atomics.h>
#include <aws/common/common.h>
#include <aws/common/ref_count.h>

#include <aws/common/clock.h>
#include <aws/common/condition_variable.h>
#include <aws/common/mutex.h>

// GCC built-in __atomic_fetch_add are not supported by seahorn
// In details, the LLVM instruction atomicrmw are not supported.
// SeaHorn crashed on original implementation.

/**
 * @brief Atomically adds a value to a 64-bit integer.
 *
 * This function performs an atomic addition operation on a 64-bit integer.
 * It atomically adds 'val' to the value pointed to by 'ptr' and returns
 * the original value of the 64-bit integer before the addition.
 *
 * @param var A pointer to an integer with type size_t wrapping by struct 
 *            aws_atomic_var to which 'value' will be added.
 * @param n The value to be added to the integer pointed to by 'var'.
 * @return The original value of the integer with type size_t before the addition.
 *
 * @note The overrided function is a simpler implmentation for seahorn. 
 *       We omit environment for multi-threading.
 */
size_t sea_atomic_fetch_add(volatile struct aws_atomic_var *var, size_t n) {
    size_t *val = (size_t *)&AWS_ATOMIC_VAR_INTVAL(var);
    size_t old_val = *val;
    *val += n;
    return old_val;
}

/**
 * Atomically subtracts n from *var, and returns the previous value of *var.
 * Uses sequentially consistent ordering.
 */
size_t sea_atomic_fetch_sub(volatile struct aws_atomic_var *var, size_t n) {
    size_t *val = (size_t *)&AWS_ATOMIC_VAR_INTVAL(var);
    size_t old_val = *val;
    *val -= n;
    return old_val;
}

void aws_ref_count_init(struct aws_ref_count *ref_count, void *object, aws_simple_completion_callback *on_zero_fn) {
    aws_atomic_init_int(&ref_count->ref_count, 1);
    ref_count->object = object;
    ref_count->on_zero_fn = on_zero_fn;
}

void *aws_ref_count_acquire(struct aws_ref_count *ref_count) {
    size_t old_value = sea_atomic_fetch_add(&ref_count->ref_count, 1);
    AWS_ASSERT(old_value > 0 && "refcount has been zero, it's invalid to use it again.");
    (void)old_value;

    return ref_count->object;
}

size_t aws_ref_count_release(struct aws_ref_count *ref_count) {
    size_t old_value = sea_atomic_fetch_sub(&ref_count->ref_count, 1);
    AWS_ASSERT(old_value > 0 && "refcount has gone negative");
    if (old_value == 1) {
        ref_count->on_zero_fn(ref_count->object);
    }

    return old_value - 1;
}
