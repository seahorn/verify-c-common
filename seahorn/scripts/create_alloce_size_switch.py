import sys, os
import fileinput
import re
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-size', type=int, help='set the maximum allocation size', required=True)
parser.add_argument('-path', type=str, help='give the relative path to generate code', required=True)
args = parser.parse_args()

libdir = args.path
max_initial_size = args.size
klee_switch_file = libdir+"/klee_switch.c"

def create_big_switch():
    func_declr = "size_t alloc_size(size_t sz) {\n  switch(sz) {\n"
    switch_case_body = ""
    switch_size = max_initial_size * 5 if max_initial_size < 100 else max_initial_size
    for i in range(1, switch_size+1): # Add a bigger switch if possible
        switch_case_body += "    case "+str(i)+": return "+str(i)+";\n"
    switch_case_body+="    default: return sz <= 4096 ? 4096 : sz;\n  }\n}\n"
    return func_declr+switch_case_body

def write_switch_into_line(switch_str):
    header_str = "\n#include <klee_switch.h>\n\n"
    try:
        file = open(klee_switch_file, 'w')
    except:
        sys.exit("output klee switch file does not exits. Exit!")
    file.write(header_str+switch_str)

def check_switch_is_consist():
    try:
        file = open(klee_switch_file, 'r')
    except:
        sys.exit("input klee switch file does not exits. Exit!")
    count = sum(1 for line in file)
    return max_initial_size > count - 4

def main():
    if check_switch_is_consist():
        switch_func = create_big_switch()
        write_switch_into_line(switch_func)
        print("Add new switch completed...")

if __name__ == '__main__':
    main()