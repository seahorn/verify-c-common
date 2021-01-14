import sys
import re
import os
import csv
import glob
import math
import subprocess
import argparse

BUILDDIR = '../build/'
BUILDABSPATH = os.path.abspath(BUILDDIR)
DATAABSPATH = os.path.abspath('../') + "/data"
HARNESS_PATH = f'{BUILDABSPATH}/seahorn/jobs'
BENCHSUBDIRS = sorted(next(os.walk(f'{BUILDDIR}/seahorn/jobs'))[1])


def get_regex_based_on_func_name(func_name):
    name_1 = r"(define|declare).*@%s\(" % func_name
    regexp1 = re.compile(name_1)
    name_2 = fr'distinct !DISubprogram\((name: \"{func_name}\"|name: "call", linkageName: \"{func_name}\")'
    regexp2 = re.compile(name_2)
    return regexp1, regexp2


def manipulate_input_data(data):
    res_data = []
    for x in data:
        if x == '\n':
            continue
        else:
            res_data.append(x)
    return res_data


def get_line_info(str_info):
    line_loc_regexp = re.compile(r'!DILocation')
    if not line_loc_regexp.search(str_info):
        return -1
    tmp_str = str_info.split("line: ")[1]
    line = tmp_str.split(",")[0]
    return line


def comput_loc_for_a_func(data, srcidx, destidx):
    max_line = -1
    loc = 0
    for idx in range(srcidx, destidx):
        get_line_info
        tmp = int(get_line_info(data[idx]))
        if tmp > max_line:
            max_line = tmp
            loc += 1
    return loc


def current_func_loc(plain_data, name):
    """
     # This function compute line of code of a given function
     # We gather line of info base on debug info
     # Once we find any info by DILocation
     # We overapproximate loc based on these line info
     # Note that we may forget some lines but the loc we collected is consistent.
     # @param plain_data stored data from .ll file.
     # @param name the function name we used
     # @return loc info if we find such function in debug info
     # we treat loc as 1 if we hit some function does not contain body of function such as malloc func.
    """
    _, name_debug_regexp = get_regex_based_on_func_name(name)
    next_function_debug_regexp = re.compile(r'distinct !DISubprogram')
    for index, plain_d in enumerate(plain_data, start=1):
        if name_debug_regexp.search(plain_d):
            for indexp, plain_dp in enumerate(
                    plain_data[index + 1:], start=index + 2):
                if next_function_debug_regexp.search(plain_dp):
                    loc = comput_loc_for_a_func(
                        plain_data, index - 1, indexp - 1)
                    return loc
            return 1  # nd function treat as one line
    raise Exception(f'the debug info of {name} must exists.')


def get_next_func_call(data, name, index):
    """
     # This function compute a function call of a function based on given function name and index
     # The function in our c file will have the following pattern:
     #      call <blah blah> <func_name> <blah blah>
     # Then it will find any function call within current function
     # Finally we gather the function call info and return.
     # @param data stored data from .ll file.
     # @param name the function name we used
     # @param index the index that we current pointed
     # @return None if we hit the end of searching (when reach the pattern '}').
     #          function name and debug function name and corresponded index on the data
    """
    func_call_regexp = re.compile(r'call.*@(?!llvm).*')
    end_of_cur_func = re.compile(r'^}')
    for index_next, line in enumerate(data[index:], start=index):
        if end_of_cur_func.search(line):
            return None, None, None  # end of searching...
        if func_call_regexp.search(line):
            func_name = line.split("@")[1].split("(")[0]
            debug_name = func_name.split(
                ".")[0] if "." in func_name else func_name
            if func_name == name:
                continue
            return debug_name, func_name, index_next
    return None, None, None


def compute_loc_of_func(data, name, total_loc, func_dict):
    """
     # This function compute line of code of each function started by main
     # We treat declare function as one line of code,
     #      those function will be either simplified code or predefined code on seahorn
     # The function recursively compute each called function on the harness
     # Then it collect loc of current function and store it into total_loc
     # @param data stored data from .ll file.
     # @param name the function name we used
     # @param total_loc the result of loc that we computed
     # @param func_dict the dictionary to store function name we already computed
     # @return nothing, use call by ref.
    """
    name_regexp, _ = get_regex_based_on_func_name(name)
    for index, plain_d in enumerate(data, start=1):
        if name_regexp.search(plain_d):
            if 'declare' in plain_d:  # no definition, assume one line code
                curr_loc = 0 if name in func_dict else 1
                func_dict[name] = "done"
            else:
                while True:
                    call_name, debug_name, index = get_next_func_call(
                        data, name, index + 1)
                    if not call_name and not debug_name:
                        break
                    if debug_name in func_dict:
                        continue
                    compute_loc_of_func(data, call_name, total_loc, func_dict)
                    func_dict[debug_name] = "done"
                curr_loc = current_func_loc(data, name)
            if args.debug:
                print(f'tot. {total_loc}, func <{name}> with loc: {curr_loc}')
            total_loc[0] += curr_loc
            break


def read_output_from_file(file_name, bench_name):
    try:
        file = open(file_name, 'r')
    except BaseException:
        sys.exit("human readable bitcode (.ll) file does not exits. Exit!")
    data = file.readlines()
    if args.debug:
        print(f'start compute loc for harness <{bench_name}>')
    main_regexp, main_debug_regexp = get_regex_based_on_func_name('main')
    res_data = ['', '']
    # 1. Add harness name
    res_data[0] = bench_name
    loc = [0]
    # 2. Add loc for each harness
    func_dict = {}  # a dictionary to store any funcs we computed
    compute_loc_of_func(data, 'main', loc, func_dict)
    res_data[1] = loc[0]
    if args.debug:
        print(f'har. {bench_name} with loc comp. {res_data[1]}...')
    file.close()
    return res_data


def run_llvmdis_for_harness(res_data):
    """
     # This function converts bitcode file into human readable files
     # The command line is 'llvm-dis-10 <file_name>.bc'
     # Then it will call function to compute loc based on .ll file
     # @param res_data store all the infor we collected.
     # @return nothing, use call by ref.
    """
    print("Start making LOC results ...")
    for benchsubdir in BENCHSUBDIRS:
        remain_path = f'{benchsubdir}/llvm-ir/{benchsubdir}.ir/{benchsubdir}.ir.bc'
        file_name = f'{HARNESS_PATH}/{remain_path}'
        command_lst = [f'llvm-dis-10 {file_name}']
        cmd_llvmdis = ""
        for strcmd in command_lst:
            cmd_llvmdis += strcmd + " ; "
        print(cmd_llvmdis)
        process = subprocess.Popen(
            '/bin/bash',
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE)
        _ = process.communicate(cmd_llvmdis.encode())
        file_name = file_name[:-2] + "ll"
        # compute the loc
        res_data.append(read_output_from_file(file_name, benchsubdir))


def write_data_into_csv(file_name, res_data):
    with open(file_name, 'w+', newline='') as csvfile:
        # create the csv writer object
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(["Name", "LOC"])
        for row in res_data:
            # data = ', '.join(row)
            csvwriter.writerow(row)


def main():
    os.makedirs(DATAABSPATH, exist_ok=True)
    os.makedirs(BUILDABSPATH, exist_ok=True)
    res_data = []
    run_llvmdis_for_harness(res_data)
    write_data_into_csv("../data/{file}".format(file='loc.csv'), res_data)


if __name__ == "__main__":
    # Args for this script
    parser = argparse.ArgumentParser(
        description='Present debug flag if using debug mode.')
    parser.add_argument('--debug', action='store_true', default=False)
    args = parser.parse_args()
    main()
