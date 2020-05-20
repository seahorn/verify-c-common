#include <stdlib.h>
#include <stdbool.h>

size_t sea_get_alloc_size(void *ptr);

bool sea_ptr_size_stored(void *ptr);

bool sea_arr_len_stored(void *arr);

size_t sea_get_arr_len(void *arr);

size_t sea_maybe_store_arr_len(void *arr, size_t len);
