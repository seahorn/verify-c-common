# verify-c-common


STEPS:

1. Clone AWS C-common project in top directory (a subdir aws-c-common will be created)
2. Call Cmake as explained in aws-c-common but use -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  * If you run step 3 from the build dir, then "install step" for aws-c-common is not needed
3. Copy compile_commands.json to top directory
4. Run: python (3) seahorn/gen_bc.py
5. Run: verify-c-common.sh
