# verify-c-common


STEPS:

1. Clone AWS C-common project in top directory
2. Call Cmake as explained in c-common but use CMAKE_EXPORT_COMPILE_COMMANDS
3. Copy compile_commands.json to top directory
4. Run: python (3) seahorn/gen_bc.py

