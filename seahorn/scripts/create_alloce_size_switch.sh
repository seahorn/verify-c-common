#!/bin/bash

# Input params
MAX_BLOCK_SIZE=$2
SOURCE_DIR=$1
FILE_NAME='klee_allocators.c'
SED='sed' 

# gsed if using mac_os
if [[ "$OSTYPE" == "darwin"* ]]; then
   SED='gsed' 
fi

# 1. Create/open a file to write a big switch by given a max block size
FUNCTION_TXT="size_t alloc_size(size_t sz) {\\n  switch(sz) {\\n"
function create_big_switch()
{
   switch_body=""
   for i in $(seq $1 $END); do
      case="    case $i: return $i;\\n"
      switch_body="$switch_body$case"
   done
   switch_end="    default: return sz <= 4096 ? 4096 : sz;\\n  }\\n}\\n"
   retval="$2$switch_body$switch_end"
}

# 2. Add switch function alloc_size into our input file
LINE_BEGIN_PATTERN='#include <nondet.h>'
LINE_END_PATTERN='void'
OUT='123'
function insert_after_line()
{
   local infile=$1 head=$2 tail=$3 newText=$4
   ${SED} -i "/$2/,/$3/{
      //!d
       /$3/i $newText
   }" ${SOURCE_DIR}/${infile}
}

create_big_switch ${MAX_BLOCK_SIZE} "$FUNCTION_TXT"
insert_after_line ${FILE_NAME} "$LINE_BEGIN_PATTERN" "$LINE_END_PATTERN" "$retval"
