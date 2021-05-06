import xml.etree.ElementTree as ET
import sys
import os
import csv
import glob
import subprocess
import argparse
from get_exper_brunch_stat import read_brunchstat_from_log, write_brunchstat_into_csv

BUILDABSPATH = os.path.abspath('../build/')
DATAABSPATH = os.path.abspath('../') + "/data"
SEAHORN_ROOT = '../../seahorn/build/run'  # Put your seahorn root dir here
FILE_DICT = {
    "": "seahorn.csv",
    "--vac": "seahorn(vac).csv",
    "--horn-bmc-solver=smt-y2": "seahorn(smt-y2).csv",
    "--cex": "seahorn(cex).csv",
    "--cex --horn-bmc-solver=smt-y2": "seahorn(cex, smt-y2).csv",
    "klee": "klee.csv"}


def get_output_level():
    if args.debug:
        output_level = sys.stdout
    else:
        output_level = subprocess.PIPE
    return output_level


def make_new_cmake_conf(use_klee, use_bleeding_edge):
    return f'cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10\
    -DCMAKE_CXX_COMPILER=clang++-10 -DSEA_ENABLE_KLEE={use_klee}\
    -DSEA_WITH_BLEEDING_EDGE={use_bleeding_edge} -DSEAHORN_ROOT={SEAHORN_ROOT} ../ -GNinja'


def read_data_from_xml(res_data):
    xml_file = glob.glob(
        "{path}/**/Test.xml".format(path=BUILDABSPATH), recursive=True)[0]
    tree = ET.parse(xml_file)
    root = tree.getroot()
    testlist = root.find('Testing')
    for test in testlist.findall('Test'):
        bench_name = test.find('Name').text
        res = test.get('Status')
        for name_measure_tag in test.find('Results').findall(
                'NamedMeasurement'):
            if name_measure_tag.attrib['name'] == 'Execution Time':
                timing = name_measure_tag.find('Value').text
        res_data.append([bench_name, timing, res])


def write_data_into_csv(file_name, res_data):
    with open(file_name, 'w+', newline='') as csvfile:
        # create the csv writer object
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(["Name", "Timing", "Result"])
        for row in res_data:
            csvwriter.writerow(row)


def collect_res_from_ctest(file_name):
    res_data = []
    read_data_from_xml(res_data)
    write_data_into_csv(
        "{dir}/{file}".format(dir="../data", file=file_name), res_data)
    print("Done, find result csv file at: %s" % file_name)

def extra_to_filename(extra, suffix='csv'):
    '''extra: --a=b --c=d to filename: a.b.c.d.csv'''
    if (len(extra) == 0):
        return f'base.{suffix}'
    parts = []
    for flag in extra:
        if flag.startswith('--'):
            flag = flag[2:]
        parts.extend(flag.split('='))
    return f'{"_".join(parts)}.{suffix}'


def run_ctest_for_seahorn():
    print("Start making SeaHorn results...")
    set_env = ''
    if extra and len(extra) > 0:
        verify_flags = " ".join(extra)
        print(f'Run SeaHorn with extra configs: {verify_flags} ')
        set_env = f'env VERIFY_FLAGS=\"{verify_flags}\"'
    cmake_conf = make_new_cmake_conf(
        "OFF", "ON" if args.bleed_edge else "OFF")
    command_lst = ["rm -rf *", cmake_conf, "ninja",
        f'{set_env} ctest -j{os.cpu_count()} -D ExperimentalTest -R . --timeout {args.timeout}']
    cddir = "cd " + BUILDABSPATH
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(cddir)
    process = subprocess.Popen(
        '/bin/bash',
        shell=True,
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(extra_to_filename(extra))
    collect_stat_from_ctest_log(extra_to_filename(extra, suffix='brunch.csv'))

def collect_stat_from_ctest_log(outfile):
    test_tmpdir = os.path.join(BUILDABSPATH, 'Testing', 'Temporary')
    logfiles = [i for i in os.listdir(
        test_tmpdir)if os.path.isfile(os.path.join(test_tmpdir, i)) and i.startswith("LastTest_")]
    latest_log = logfiles[0]
    print("collecting brunch stat from " + logfiles[0])
    data = read_brunchstat_from_log(os.path.join(test_tmpdir, latest_log))
    outpath = os.path.join(DATAABSPATH, outfile)
    write_brunchstat_into_csv(data, outpath)



def run_ctest_for_klee():
    use_klee = "ON"
    cmake_conf = make_new_cmake_conf("ON", "ON" if args.bleed_edge else "OFF")
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -D ExperimentalTest -R klee_ --timeout 2000']
    print("Start making KLEE results...")
    cddir = "cd " + BUILDABSPATH
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(cddir)
    process = subprocess.Popen(
        '/bin/bash',
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(FILE_DICT["klee"])


def main():
    os.makedirs(DATAABSPATH, exist_ok=True)
    os.makedirs(BUILDABSPATH, exist_ok=True)
    if args.seahorn:
        run_ctest_for_seahorn()
    if args.klee:
        run_ctest_for_klee()


if __name__ == "__main__":
    # Args for this script
    parser = argparse.ArgumentParser(
        description='Present flags to decide which tool will be tested.')
    parser.add_argument('--seahorn', action='store_true', default=True)
    parser.add_argument('--klee', action='store_true', default=False)
    parser.add_argument('--bleed_edge', action='store_true', default=False)
    parser.add_argument('--debug', action='store_true', default=False)
    parser.add_argument('--timeout', type=int, default=2000,
        help='Seconds before timeout for each test')
    args, extra = parser.parse_known_args()
    if args.klee:
        args.seahorn = False
    main()
