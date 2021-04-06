import sys, os
import re
import csv
import argparse
import subprocess
​
# parser = argparse.ArgumentParser()
# parser.add_argument('-csv', type=str, help='give an output csv name', required=True)
# args = parser.parse_args()
​
BENCHDIR = '../'
BENCHDIRABSPATH = os.path.abspath(BENCHDIR)
TABLEFILE = 'aws-cbmc.csv'
PATTERN = re.compile(".*log$")
ATTRS = ['bench name', 'total times (s)', 'vc gen times (s)', 'dec proc times (s)', 'symb exec times (s)', 'postprocess eq (s)', 'SSA times (s)', 'solver times (s)', 'iterations', 'result (success/fail)']
BENCHSUBDIRS = []
​
def convert_time_to_seconds(str_time):
    m, s = str_time.split("m")
    _, m = m.split("real")
    s = s[:-1]
    m,s = int(m), float(s)
    result = m * 60 + s
    return result
​
def manipulate_input_data(data):
    res_data = []
    for x in data:
        if x == '\n':
            continue
        else:
            res_data.append(x)
    return res_data
​
def add_time_format(timing_data):
    _, raw_time = timing_data.replace(" ", "").split(":")
    return "{:0.3f}".format(round(float(raw_time[:-1]), 3))
​
def read_output_from_file(benchsubdir, file_name):
    """
        According to src files on cbmc:
            https://github.com/diffblue/cbmc/blob/develop/src/goto-checker/bmc_util.cpp#L401-L417
        decision procedure time includes solver time
            https://github.com/diffblue/cbmc/blob/develop/src/solvers/prop/prop_conv_solver.cpp#L475-L477
        post process does not perform any functionality, ignore statistic here
    """
    try:
        file = open(file_name, 'r')
    except:
        sys.exit("result file does not exits. Exit!")
    data = file.readlines()
    res_data = []
    for i in range(len(ATTRS)):
        res_data.append('')
    plain_data = manipulate_input_data(data)
    plain_data = [d.replace("\t", "").replace("\n", "") for d in plain_data]
    # 1. Add benchname
    res_data[0] = benchsubdir
    success_regexp = re.compile(r'SUCCESSFUL')
    failed_regexp = re.compile(r'FAILED')
    symbolic_ex_regexp = re.compile(r'Runtime Symex')
    postps_eq_regexp = re.compile(r'Runtime Postprocess Equation')
    ssa_regexp = re.compile(r'Runtime Convert SSA')
    decision_regexp = re.compile(r'Runtime decision procedure')
    solver_regexp = re.compile(r'Runtime Solver:')
    iterations_regexp = re.compile(r'iterations')
    tol_timing_regexp = re.compile(r'^real')
    for plain_d in plain_data:
        if tol_timing_regexp.search(plain_d):
            # 2. Add total timing
            total_timing = round(convert_time_to_seconds(plain_d), 3)
            format_total_timing = "{:0.3f}".format(total_timing)
            res_data[1] = format_total_timing
        if iterations_regexp.search(plain_d):
            # 3. Add iterations
            _, rawd = plain_data[-5].split('(')
            iters, _ = rawd.split(' ')
            res_data[-2] = iters
        if decision_regexp.search(plain_d):
            # 4. Add the decision procedure times (iterations)
            res_data[3] = add_time_format(plain_d)
        # 5. Add pass/fail results
        if success_regexp.search(plain_d):
            res_data[-1] = "success"
        if failed_regexp.search(plain_d):
            res_data[-1] = "fail"
        if symbolic_ex_regexp.search(plain_d):
            # 6. Add symbolic execution times
            res_data[4] = add_time_format(plain_d)
        if postps_eq_regexp.search(plain_d):
            # 7. Add post process eq times
            res_data[5] = add_time_format(plain_d)
        if ssa_regexp.search(plain_d):
            # 8. Add SSA times
            res_data[6] = add_time_format(plain_d)
        if solver_regexp.search(plain_d):
            # 9. Add solver times
            res_data[7] = add_time_format(plain_d)
    res_data[2] = 0.0
    for i in range(1, 8):
        if res_data[i] == '': res_data[i] = "0.000"
    for i in range(4, 7):
        # 10. Add verification condition generator times
        res_data[2] += float(res_data[i])
    res_data[2] = "{:0.3f}".format(round(res_data[2], 3))
    if res_data[-1] == '':
         res_data[-1] = "undefined"
    if res_data[3] != '' and float(res_data[1]) < float(res_data[3]):
        # print(res_data[1], res_data[3])
        print(f'Bench {benchsubdir} recording error! Please check log file on that folder.')
    file.close()
    return res_data
​
def get_all_res_from_log_file(table_lst):
    idx_output = 0
    for benchsubdir in BENCHSUBDIRS:
        log_path = "../"+benchsubdir+"/logs/result.txt"
        res_data = read_output_from_file(benchsubdir, log_path)
        table_lst.append(res_data)
​
def search_get_all_subdirse():
    global BENCHSUBDIRS
    BENCHSUBDIRS = sorted(next(os.walk(BENCHDIR))[1])[:-1]
    # BENCHSUBDIRS = BENCHSUBDIRS[:1]
    # print(os.getcwd())
​
def run_benchs_cbmc():
    command_lst = ["rm -rf gotos logs log", "( time make result; ) 2> log", "cat log >> logs/result.txt "]
    print("Start making results ...")
    for benchsubdir in BENCHSUBDIRS:
        benchsubdirabspath = BENCHDIRABSPATH + '/' + benchsubdir
        cddir = "cd ../"+benchsubdir
        for strcmd in command_lst:
            cddir += " ; " + strcmd
        print(cddir)
        process = subprocess.Popen('/bin/bash', stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        _ = process.communicate(cddir.encode())
    print("Benchmark end-of-run. Start gathering info...")
​
def write_info_into_csv(table_lst):
    print(f'Writing data into {TABLEFILE} at current directory...')
    try:
        file = open(TABLEFILE, 'w')
    except:
        sys.exit("output table file does not exits. Exit!")
    strs = ','.join(ATTRS)
    file.write(strs+'\n')
    file.close()
    with open(TABLEFILE, 'a', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',',
                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
        for out_data in table_lst:
            writer.writerow(out_data)
​
def main():
    table_list = []
    search_get_all_subdirse()
    run_benchs_cbmc()
    get_all_res_from_log_file(table_list)
    write_info_into_csv(table_list)
​
if __name__ == '__main__':
	main()
