# verify-c-common

## Setup AWS-C-COMMON
This is a common step for all other configurations.

1. Clone [aws-c-common](https://github.com/awslabs/aws-c-common) project in the root directory of the project so that a
   sub-directory `aws-c-common` is created
   ```bash
   $ git clone https://github.com/awslabs/aws-c-common
   ```

2. Configure `aws-c-common` as instructed, use `clang`, and the following commands:
   ```bash
   $ cd aws-c-common ; mkdir build ; cd build ; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../ ; cd ../../ ; ln -sf aws-c-common/build/compile_commands.json .
   ```

## Compile verification harness using CMake

1. Create a build directory
```bash
$ mkdir build ; cd build
```
2. Configure with cmake
```bash
$ cmake -DSEA_LINK=llvm-link -DSEAHORN_ROOT=<SEAHORN_ROOT> ../ -GNinja
```
use additional options to ensure that `clang` is chosen as the default compiler
3. Compile
```bash
$ ninja
```
4. Verify
```bash
$ ninja test
```
5. Run individual test
```bash
$ ctest -R <TEST_NAME>
```
6. Run individual file manually
```bash
$ bash verify-c-common.sh <FILE_NAME> <sat|unsat>
```
7. Run individual file manually manually:
```
# Find command starting with 'sea fpf ...' above and copy-paste
$ sea fpf ...
```

Compiled bitcode files are placed under `build/seahorn/jobs/<NAME>/llvm-ir/<NAME>.bc`


