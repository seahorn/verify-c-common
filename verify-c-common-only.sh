#!/bin/bash
# This script either runs sea fpf on a particular out.bc file or runs them on all out.bc files
# under a given directory including subdirs.
# to see the commands run, start script with bash -x
# The above is an easy way to get sea cmdline
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)

col=10 # change this to whatever column you want the output to start at

: ${1?"Usage: $0 <bitcode_file> <sea_dir>  Need to pass bitcode file from trusty"}
: ${2:?"Usage: $0 <bitcode_file> <sea_dir> Need to pass SEA_DIR - i.e. the dir which contains the sea{,horn,opt} cmds e.g. seahorn/build/run/bin/"}


function runOnFile {
    INPUT_FILE=${1}
    SEA_DIR=${2}
    OTHER_FLAGS=${4}
    VERBOSE=${3}

    cmd=''
    cmd+="${SEA_DIR}/sea bpf --sea-dsa=cs+t  -O3  --inline  --horn-bmc-engine=mono --horn-bmc --horn-bv2=true \
                       --log=opsem  --sea-opsem-allocator=normal  --keep-shadows=true --horn-bv2-simplify=true \
                       --horn-bv2-lambdas --horn-gsa --horn-vcgen-use-ite --horn-bv2-ptr-size=8 --horn-bv2-word-size=1 \
                       --horn-bv2-extra-widemem=false --keep-temps --temp-dir=/tmp/verify-c-common \
                       --lower-gv-init --lower-gv-init-struct=false  -S  --devirt-functions \
                       --externalize-addr-taken-functions --keep-shadows \
		       --horn-bv2-singleton-aliases=true --horn-stats=true \
                       --horn-unify-assumes=true --horn-vcgen-only-dataflow=true --horn-bmc-coi=true \
                       ${INPUT_FILE} --sea-dsa-type-aware \
                       --horn-explicit-sp0=false $OTHER_FLAGS "
    if [ $VERBOSE -eq 1 ]; then
	cmd+="| tee /dev/tty "
    else
	cmd+="2> /dev/null "
    fi
    cmd+="| egrep -c \"^unsat$\""
    r=$(eval $cmd)
    return $r
    
}

function printResult {
    INPUT_FILE=$1
    PASS=$2
    if [ $PASS -eq 1 ]; then
	printf '%s%*s\t%s%s\n' "$GREEN" $col "[OK]" "$NORMAL" "$INPUT_FILE"
    else
        printf '%s%*s\t%s%s\n' "$RED" $col "[FAIL]" "$NORMAL" "$INPUT_FILE"
    fi

}

INPUT_FILE=${1}
SEA_DIR=${2}
OTHER_FLAGS=${@:3}

if [[ -d ${INPUT_FILE} ]]; then
   shopt -s globstar
   for f in $INPUT_FILE/**/out.bc; do  # Whitespace-safe and recursive 
       runOnFile "$f" $SEA_DIR "0" $OTHER_FLAGS 
       printResult "$f" $?
   done
else
    runOnFile $INPUT_FILE $SEA_DIR "1" $OTHER_FLAGS 
    result=$?
    if [ $result -eq 1 ]; then
	exit 0
    else
	exit 1
    fi
fi
