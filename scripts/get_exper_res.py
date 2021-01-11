import xml.etree.ElementTree as ET
import sys
import os
import csv
import glob
import subprocess

builddir = '../build/'
buildabspath = os.path.abspath(builddir)
dataabspath = os.path.abspath('../') + "/data"
seahorn_root = '../../seahorn'  # Put your seahorn root dir here
file_dict = {
    "": "seahorn.csv",
    "--vac": "seahorn(vac).csv",
    "--horn-bmc-solver=smt-y2": "seahorn(smt-y2).csv",
    "--cex": "seahorn(cex).csv",
    "--cex --horn-bmc-solver=smt-y2": "seahorn(cex, smt-y2).csv",
    "klee": "klee.csv"}


def make_new_cmake_conf(use_klee):
    return f'cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10\
    -DCMAKE_CXX_COMPILER=clang++-10 -DSEA_ENABLE_KLEE={use_klee}\
    -DSEAHORN_ROOT={seahorn_root} ../ -GNinja'


def read_data_from_xml(res_data):
    xml_file = glob.glob(
        "{path}/**/Test.xml".format(path=buildabspath), recursive=True)[0]
    tree = ET.parse(xml_file)
    root = tree.getroot()
    testlist = root.find('Testing')
    for test in testlist.findall('Test'):
        bench_name = test.find('Name').text
        res = test.get('Status')
        timing = test.find('Results').findall(
            'NamedMeasurement')[0].find('Value').text
        res_data.append([bench_name, timing, res])


def write_data_into_csv(file_name, res_data):
    with open(file_name, 'w+', newline='') as csvfile:
        # create the csv writer object
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(["Name", "Timing", "Result"])
        for row in res_data:
            # data = ', '.join(row)
            csvwriter.writerow(row)


def collect_res_from_ctest(file_name):
    res_data = []
    read_data_from_xml(res_data)
    write_data_into_csv(
        "{dir}/{file}".format(dir="../data", file=file_name), res_data)


def run_ctest_for_seahorn():
    env_lst = ["", "--vac", "--horn-bmc-solver=smt-y2",
               "--cex", "--cex --horn-bmc-solver=smt-y2"]
    print("Start making SeaHorn results ...")
    for verify_flag in env_lst:
        cmake_conf = make_new_cmake_conf("OFF")
        command_lst = ["rm -rf *", cmake_conf, "ninja",
                       f'env VERIFY_FLAGS={verify_flag} ctest -D ExperimentalTest -R . --timeout 2000']
        cddir = "cd " + buildabspath
        for strcmd in command_lst:
            cddir += " ; " + strcmd
        print(cddir)
        process = subprocess.Popen('/bin/bash', stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        _ = process.communicate(cddir.encode())
        collect_res_from_ctest(file_dict[verify_flag])


def run_ctest_for_klee():
    use_klee = "ON"
    cmake_conf = make_new_cmake_conf("ON")
    command_lst = ["rm -rf *", cmake_conf, "ninja",
                   f'ctest -D ExperimentalTest -R klee_ --timeout 2000']
    print("Start making KLEE results ...")
    cddir = "cd " + buildabspath
    for strcmd in command_lst:
        cddir += " ; " + strcmd
    print(cddir)
    process = subprocess.Popen(
        '/bin/bash',
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE)
    _ = process.communicate(cddir.encode())
    collect_res_from_ctest(file_dict["klee"])


def main():
    os.makedirs(dataabspath, exist_ok=True)
    os.makedirs(buildabspath, exist_ok=True)
    run_ctest_for_seahorn()
    run_ctest_for_klee()


if __name__ == "__main__":
    main()
