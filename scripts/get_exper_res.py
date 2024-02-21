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
SEAHORN_ROOT = '/home/yusen/seawork/seahorn/build/run'  # Put your seahorn root dir here
FILE_DICT = {
    "": "seahorn.csv",
    "--vac": "seahorn(vac).csv",
    "--horn-bmc-solver=smt-y2": "seahorn(smt-y2).csv",
    "--cex": "seahorn(cex).csv",
    "--cex --horn-bmc-solver=smt-y2": "seahorn(cex, smt-y2).csv",
    "klee": "klee.csv", "symbiotic": "symbiotic.csv", "clam": "clam.csv"}
LLVM_VERSION=14

def extra_to_filename(extra, suffix='.csv', prefix=''):
    '''extra: --a=b --c=d to filename: a.b.c.d.csv'''
    if (len(extra) == 0):
        return f'base{suffix}'
    parts = []
    for flag in extra:
        if flag.startswith('--'):
            flag = flag[2:]
        parts.extend(flag.split('='))
    return f'{prefix}{"_".join(parts)}{suffix}'


def make_build_path(extra, build_path='../build'):
    build_path += extra_to_filename(extra, '', '_') if extra else '_base'
    print(f'[Build Path] {build_path}')
    if not os.path.exists(build_path):
        os.mkdir(build_path)
    global BUILDABSPATH
    BUILDABSPATH = os.path.abspath(build_path)


def get_output_level():
    if args.debug:
        output_level = sys.stdout
    else:
        output_level = subprocess.PIPE
    return output_level


def make_new_cmake_conf():
    use_klee = "ON" if args.klee else "OFF"
    use_symbiotic = "ON" if args.symbiotic else "OFF"
    use_bleeding_edge = "ON" if args.bleed_edge else "OFF"
    # use_crab = "ON" if "--crab" in extra else "OFF"
    if args.smack_parser:
        use_smack = "ON" if args.smack else "OFF"
        smack_enable_no_mem_split = "ON" if args.mem_no_split else "OFF"
        smack_args = f'-DSEA_ENABLE_SMACK={use_smack} -DSMACK_ENCODING={args.precise} -DSMACK_PROPERTY_CHECK={args.checks}\
        -DSMACK_ENABLE_NO_MEM_SPLIT={smack_enable_no_mem_split}'
    else:
        smack_args = ""
    return f'cmake -DSEA_LINK=llvm-link-{LLVM_VERSION} -DCMAKE_C_COMPILER=clang-{LLVM_VERSION}\
    -DCMAKE_CXX_COMPILER=clang++-{LLVM_VERSION} -DSEA_ENABLE_KLEE={use_klee} {smack_args}\
    -DSEA_WITH_BLEEDING_EDGE={use_bleeding_edge} -DSEA_ENABLE_CRAB=OFF\
    -DSEA_ENABLE_SYMBIOTIC={use_symbiotic} -DSEAHORN_ROOT={SEAHORN_ROOT} ../ -GNinja'


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


def run_ctest_for_seahorn():
    print("[SeaHorn] Start making SeaHorn results...")
    set_env = ''
    if extra and len(extra) > 0:
        verify_flags = " ".join(extra)
        print(f'Run SeaHorn with extra configs: {verify_flags} ')
        set_env = f'env VERIFY_FLAGS=\"{verify_flags}\"'
    cmake_conf = make_new_cmake_conf()
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'{set_env} ctest -j 12 -D ExperimentalTest -R . --timeout {args.timeout}']
    make_build_path(extra)
    cddir = "cd " + BUILDABSPATH
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(f'[Command] {cddir}')
    process = subprocess.Popen(
        '/bin/bash',
        shell=True,
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(extra_to_filename(extra))
    collect_stat_from_ctest_log(extra_to_filename(extra, suffix='.brunch.csv'),
                                True if "--crab" in extra else False)

def run_ctest_for_clam():
    print("[Clam] Start making Clam results...")
    cmake_conf = make_new_cmake_conf()
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -j{os.cpu_count()} -D ExperimentalTest -R smack_ --timeout 200']
    make_build_path(["--clam"])
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(f'[Command] {cddir}')
    process = subprocess.Popen(
        '/bin/bash',
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(FILE_DICT["klee"])

def collect_stat_from_ctest_log(outfile, use_crab):
    test_tmpdir = os.path.join(BUILDABSPATH, 'Testing', 'Temporary')
    logfiles = [i for i in os.listdir(test_tmpdir)if os.path.isfile(
        os.path.join(test_tmpdir, i)) and i.startswith("LastTest_")]
    latest_log = logfiles[0]
    print("collecting brunch stat from " + logfiles[0])
    if args.seahorn:
        data = read_brunchstat_from_log(os.path.join(test_tmpdir, latest_log))
        outpath = os.path.join(DATAABSPATH, outfile)
        write_brunchstat_into_csv(data, outpath)
    elif args.symbiotic:
        data = read_symbiotic_bruchstat_from_log(os.path.join(
            test_tmpdir, latest_log), BUILDABSPATH, args.timeout)
        outpath = os.path.join(DATAABSPATH, outfile)
        write_symbiotic_bruchstat_into_csv(data, outpath)

def run_ctest_for_klee():
    cmake_conf = make_new_cmake_conf()
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -j{os.cpu_count()} -D ExperimentalTest -R klee_ --timeout {args.timeout}']
    print("[KLEE] Start making KLEE results...")
    make_build_path(["--klee"])
    cddir = "cd " + BUILDABSPATH
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(f'[Command] {cddir}')
    process = subprocess.Popen(
        '/bin/bash',
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(FILE_DICT["klee"])


def run_ctest_for_smack():
    cmake_conf = make_new_cmake_conf()
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -j{os.cpu_count()} -D ExperimentalTest -R smack_ --timeout 200']
    print("[SMACK] Start making SMACK results...")
    make_build_path(["--smack"])
    cddir = "cd " + BUILDABSPATH
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    if args.debug:
        print(f'[Command] {cddir}')
    process = subprocess.Popen(
        '/bin/bash',
        stdin=subprocess.PIPE,
        stdout=get_output_level())
    _ = process.communicate(cddir.encode())
    mem_split = 'mem_no_split' if args.mem_no_split else 'mem_split'
    collect_res_from_ctest(extra_to_filename(
        [str(args.precise), str(args.checks), mem_split]))

def run_ctest_for_symbiotic():
    cmake_conf = make_new_cmake_conf()
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -j{os.cpu_count()} -D ExperimentalTest -R symbiotic_ --timeout {args.timeout}']
    print("Start making Symbiotic results...")
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
    collect_stat_from_ctest_log(FILE_DICT["symbiotic"])

def main():
    os.makedirs(DATAABSPATH, exist_ok=True)
    os.makedirs(BUILDABSPATH, exist_ok=True)
    if args.seahorn:
        run_ctest_for_seahorn()
    if args.klee:
        run_ctest_for_klee()
    if args.smack_parser:
        run_ctest_for_smack()
    if args.symbiotic:
        run_ctest_for_symbiotic()
    if args.clam:
        run_ctest_for_clam()


if __name__ == "__main__":
    # Args for this script
    parser = argparse.ArgumentParser(
        description='Present flags to decide which tool will be tested.')
    parser.add_argument('--seahorn', action='store_true', default=True)
    parser.add_argument('--klee', action='store_true', default=False)
    parser.add_argument('--symbiotic', action='store_true', default=False)
    parser.add_argument('--clam', action='store_true', default=False)
    parser.add_argument('--bleed_edge', action='store_true', default=False)
    parser.add_argument('--debug', action='store_true', default=False)
    parser.add_argument('--timeout', type=int, default=2000,
                        help='Seconds before timeout for each test')
    subparsers = parser.add_subparsers(
        help='sub-commands help', dest="smack_parser")
    smack_parser = subparsers.add_parser('smack', help="smack help")
    smack_parser.add_argument('--smack', action='store_true', default=False)
    smack_parser.add_argument(
        '--precise',
        type=str,
        default='unbounded-integer',
        help='Set Smack precise: unbounded-integer or bit vector')
    smack_parser.add_argument(
        '--checks',
        type=str,
        default='assertions',
        help='Set Smack property checks: assertions or valid-deref')
    smack_parser.add_argument(
        '--mem_no_split',
        action='store_true',
        default=False,
        help='Set Smack uses no memory split')
    args, extra = parser.parse_known_args()
    if args.klee:
        args.seahorn = False
    if args.smack_parser:
        args.seahorn = False
    if args.symbiotic:
        args.seahorn = False
    main()