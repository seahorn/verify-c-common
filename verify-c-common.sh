#!/bin/bash

: ${1?"Usage: $0 <bitcode_file> <sea_dir>  Need to pass bitcode file from trusty"}
: ${2:?"Usage: $0 <bitcode_file> <sea_dir> Need to pass SEA_DIR - i.e. the dir which contains the sea{,horn,opt} cmds e.g. seahorn/build/run/bin/"}

INPUT_FILE=${1}
shift
SEA_DIR=${1}
shift

${SEA_DIR}/sea fpf --sea-dsa=cs+t  -m32 -O0  --inline  --horn-bmc-engine=mono --horn-bmc --horn-bv2=true \
                   --log=opsem  --sea-opsem-allocator=normal  --keep-shadows=true --horn-bv2-simplify=true \
                   --horn-bv2-lambdas --horn-gsa --horn-vcgen-use-ite --horn-bv2-ptr-size=8 --horn-bv2-word-size=8 \
                   --horn-bv2-extra-widemem --keep-temps --temp-dir=/tmp/verify-c-common \
                   --lower-gv-init --lower-gv-init-struct=false  -S  --devirt-functions \
                   --externalize-addr-taken-functions --keep-shadows \
		   --horn-bv2-singleton-aliases=true --horn-stats=true \
                   --horn-unify-assumes=true --horn-vcgen-only-dataflow=true --horn-bmc-coi=true \
                   ${INPUT_FILE} --sea-dsa-type-aware \
                   --horn-explicit-sp0=false $@
