#!/bin/bash
# This script either runs sea fpf on a particular out.bc file or runs them on all out.bc files
# under a given directory including subdirs.
# to see the commands run, start script with bash -x
# The above is an easy way to get sea cmdline
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"
VERIFICATION_BASE_CONFIG="$SCRIPT_DIR/seahorn/sea_base.yaml"
GET_JOB_OPT_SCRIPT="$SCRIPT_DIR/seahorn/get_job_options.py" 

col=10 # change this to whatever column you want the output to start at
gen_cmd_line=''

: ${1?"Usage: $0 <bitcode_file> <sea_dir>  Need to pass bitcode file from trusty"}
: ${2:?"Usage: $0 <bitcode_file> <sea_dir> Need to pass SEA_DIR - i.e. the dir which contains the sea{,horn,opt} cmds e.g. seahorn/build/run/bin/"}


function getCmdLine {
    CMD_LINE='python3 '
    CMD=$1
    BASE_CONFIG=$2
    JOB_CONFIG=$3
    CMD_LINE+="$CMD --base_config=$BASE_CONFIG --job_config=$JOB_CONFIG" 
    gen_cmd_line=$(eval $CMD_LINE)
}

function runOnFile {
    INPUT_FILE=${1}
    SEA_DIR=${2}
    VERBOSE=${3}
    FLAGS=${4}
    OTHER_FLAGS=${5}
    
    cmd=''
    cmd+="${SEA_DIR}/sea fpf $FLAGS $OTHER_FLAGS $INPUT_FILE "
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
       sea_yaml="$(dirname $f)/../sea.yaml"
       getCmdLine $GET_JOB_OPT_SCRIPT $VERIFICATION_BASE_CONFIG $sea_yaml               
       runOnFile $f $SEA_DIR "0" "$gen_cmd_line" "$OTHER_FLAGS" 
       printResult "$f" $?
   done
else
    sea_yaml="$(dirname $INPUT_FILE)/../sea.yaml"
    getCmdLine $GET_JOB_OPT_SCRIPT $VERIFICATION_BASE_CONFIG $sea_yaml               
    runOnFile $INPUT_FILE $SEA_DIR "1" "$gen_cmd_line" "$OTHER_FLAGS" 
    result=$?
    if [ $result -eq 1 ]; then
	exit 0
    else
	exit 1
    fi
fi
