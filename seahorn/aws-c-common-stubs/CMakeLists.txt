add_library(priority_queue
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c)
sea_attach_bc(priority_queue)

# Change linkage to all functions that start with 's_' to external
# This is necessary so that they can be called directly from verification harness
set(LLVMIR_OPT ${SEA_PP})
llvmir_attach_opt_pass_target(TARGET priority_queue.opt.ir DEPENDS priority_queue.ir
  "--externalize-function=^s_*" "-externalize-functions-delete=false" "--externalize-fns")

add_library(sift_either_override s_sift_either_override.c)
sea_attach_bc(sift_either_override)

add_library(sift_up_override s_sift_up_override.c)
sea_attach_bc(sift_up_override)

add_library(remove_node_override s_remove_node_override.c)
sea_attach_bc(remove_node_override)

add_library(byte_cursor_advance_nospec_override byte_cursor_advance_nospec_override.c)
sea_attach_bc(byte_cursor_advance_nospec_override)

add_library(hash_table
  ${AWS_C_COMMON_ROOT}/source/hash_table.c)
sea_attach_bc(hash_table)

# Change linkage to all functions that start with 's_' to external
# This is necessary so that they can be called directly from verification harness
llvmir_attach_opt_pass_target(TARGET hash_table.opt.ir DEPENDS hash_table.ir
  "--externalize-function=^s_*" "-externalize-functions-delete=false" "--externalize-fns")

add_library(update_template_size_override s_update_template_size_override.c)
sea_attach_bc(update_template_size_override)

add_library(hash_table_state_is_valid_bounded hash_table_state_is_valid_bounded_override.c)
sea_attach_bc(hash_table_state_is_valid_bounded)
