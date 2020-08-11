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
    cmd+="${SEA_DIR}/sea fpf --inline -O3 \
                       --enable-loop-idiom --enable-indvar \
                       --no-lower-gv-init-struct --externalize-addr-taken-functions \
                       --horn-unify-assumes=true \
                       --horn-gsa --horn-vcgen-use-ite \
                       --dsa=sea-cs-t --devirt-functions=types \
                       --bmc=opsem \
                       --horn-vcgen-only-dataflow=true --horn-bmc-coi=true \
                       --sea-opsem-allocator=static 
                       --horn-bv2-lambdas --horn-bv2-simplify=true \
                       --horn-bv2-extra-widemem \
                       -S --keep-temps --temp-dir=/tmp/verify-c-common \
		       --horn-stats=true \
                       --horn-explicit-sp0=false \
                       $OTHER_FLAGS \
                       ${INPUT_FILE}"

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
