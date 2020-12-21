# verify-c-common

![os](https://img.shields.io/badge/os-linux-orange?logo=linux)
![os](https://img.shields.io/badge/os-macos-silver?logo=apple)
[![Azure DevOps builds](https://img.shields.io/azure-devops/build/seahorn/verify-c-common/2)](https://dev.azure.com/seahorn/verify-c-common/_build)
[![CI](https://github.com/seahorn/verify-c-common/workflows/CI/badge.svg)](https://github.com/seahorn/verify-c-common/actions?query=workflow%3ACI)

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
$ cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=<SEAHORN_ROOT> ../ -GNinja
```
use additional options to ensure that `clang` is chosen as the default compiler
3. Compile
```bash
$ ninja
```
or
```bash
$ cmake --build .
```
4. Verify
```bash
$ ninja test
```
or
```bash
$ cmake --build . --target test
```
5. Run individual test
```bash
$ ctest -R <TEST_NAME>
```
6. Run individual file manually
```bash
$ ./verify [--cex] <BC_FILE_NAME> 
```

The `--cex` generates a counterexample, but also changes configuration options
to yield more readable results. This might negatively affect the verification
time.

Compiled bitcode files are placed under `build/seahorn/jobs/<NAME>/llvm-ir/<NAME>.bc`

The following sequence of commands work for me
```
$ git clone https://github.com/yvizel/verify-c-common.git
$ cd verify-c-common
$ git clone https://github.com/awslabs/aws-c-common.git
$ mkdir build
$ cd build
$ cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn ../ -GNinja
$ cmake --build .
$ ctest
```

