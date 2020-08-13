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

## Compile verification harnesses using Python script

1. Use `seahorn/gen_bc.py` script to generate all harnesses
```bash
$ SEA=<PATH_TO_SEA> python3 seahorn/gen_bc.py
```
where `<PATH_TO_SEA>` is a path to the SeaHorn **binary** directory, e.g., `/opt/seahorn/bin`

By default, `gen_bc.py` compiles all jobs under `seahorn/jobs`. Individual jobs
can be specified on command line. 

Compiled bitcode for a job `seahorn/jobs/NAME` is placed into `seahorn/jobs/NAME/build/out.bc`

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
Compiled bitcode files are placed under `build/seahorn/jobs/<NAME>/llvm-ir/<NAME>.bc`

## Running SeaHorn
A script is provided to run all jobs or an individual job.
To run all jobs:
```bash
$ bash verify-c-common.sh seahorn/jobs <SEAHORN_ROOT> <EXTRA_OPTS>
```
where `<SEAHORN_ROOT>` is the root of SeaHorn distribution, e.g., `/opt/seahorn`, 
and `<EXTRA_OPTS>` are any additional options that are passed to `sea`.

To run an individual job:
```bash
$ bash verify-c-common.sh seahorn/jobs/NAME/build/out.bc <SEAHORN_ROOT> <EXTRA_OPTS>
```
where `NAME` is a name of a job. This assumes that `out.bc` is the compiled bitcode. Change as appropriate.

Verification options can be changed by modifying `seahorn/sea.yaml` and `seahorn/jobs/NAME/sea.yaml` files.

