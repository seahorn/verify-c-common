import os
import sys
import argparse
import subprocess
import shutil

VCC_ROOT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_BUILD_DIR = os.path.join(VCC_ROOT_DIR, 'build')
COV_DIRNAME = 'fuzz_coverage'
CORPUS_DIRNAME = 'corpus'
RAW_NAME = 'default.profraw'
DATA_NAME = 'default.profdata'
ALL_FUZZ_FILENAME = 'all_fuzz.info'
LLVM_COV = shutil.which('llvm-cov-10')
LLVM_PROFDATA = shutil.which('llvm-profdata-10')
LCOV = shutil.which('lcov')
GENHTML = shutil.which('genhtml')


def _generate_coverage_data(fuzz_binary, out_dir):
  print("Generating coverage for {} ...".format(fuzz_binary))
  job_dir = os.path.dirname(fuzz_binary)
  fuzz_cmd = [
    fuzz_binary,
    os.path.join(job_dir, CORPUS_DIRNAME),
    '-runs=0',
    '-detect_leaks=0'
  ]
  # subprocess.check_call(fuzz_cmd)
  fuzz_process = subprocess.Popen(fuzz_cmd, shell=False,
                             encoding='utf-8',
                             errors='ignore',
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT,
                             env={'ASAN_OPTIONS':'detect_leaks=0'})
  rcode = fuzz_process.wait()
  fuzz_process.stdout.close()
  if rcode != 0:
    print("{} went wrong...".format(fuzz_binary))
    return

  # llvm-profdata-10 merge -sparse default.profraw -o default.profdata
  merge_cmd = [
    LLVM_PROFDATA,
    'merge',
    '-sparse',
    os.path.join(job_dir, RAW_NAME),
    '-o',
    os.path.join(job_dir, DATA_NAME)
  ]
  subprocess.check_call(merge_cmd)

  trace_file_name = os.path.join(out_dir, '{}.info'.format(os.path.basename(job_dir)))
  trace_file = open(trace_file_name, 'w+')
  print("Exporting lcov trace file to {}".format(trace_file_name))
  # llvm-cov-10 export fuzz -instr-profile=default.profdata > <ouput>
  export_cmd = [
    LLVM_COV,
    'export',
    fuzz_binary,
    '-instr-profile={}'.format(os.path.join(job_dir, DATA_NAME)),
    '-format=lcov'
  ]
  export_process = subprocess.Popen(
    export_cmd,
    shell=False,
    encoding='utf-8',
    errors='ignore',
    stdout=trace_file,
    stderr=subprocess.STDOUT,
  )
  export_res = export_process.wait()
  if export_res != 0:
    print("llvm-cov failed, look in {}".format(trace_file_name))
  trace_file.close()
  return


def main(args):
  build_dir = os.path.expanduser(args.build_dir)
  if not os.path.isdir(build_dir):
    print("Please provide full path to build directory")
    return
  if not LLVM_COV or not LLVM_PROFDATA:
    print("No llvm-cov-10 or llvm-profdata available!")
    return
  print("Collecting fuzzing coverage in {}".format(build_dir))
  data_dir = os.path.join(VCC_ROOT_DIR, 'data')
  os.makedirs(data_dir, exist_ok=True)
  coverage_dir = os.path.join(data_dir, COV_DIRNAME)
  os.makedirs(coverage_dir, exist_ok=True)

  job_dirs = sorted(next(os.walk(os.path.join(build_dir, 'seahorn', 'jobs')))[1])
  for job in job_dirs:
    job_dir = os.path.join(build_dir, 'seahorn', 'jobs', job)
    fuzz_binary = "{}_fuzz".format(job)
    fuzz_binary = os.path.join(job_dir, fuzz_binary)
    if (not os.path.exists(fuzz_binary)) or (not os.path.isfile(fuzz_binary)):
      continue
    _generate_coverage_data(fuzz_binary, coverage_dir)

  _, _, trace_files = next(os.walk(coverage_dir))
  lcov_cmd = [LCOV]
  for trace in trace_files:
    trace_path = os.path.join(coverage_dir, trace)
    if os.path.exists(trace_path) and os.path.isfile(trace_path):
      lcov_cmd.extend(['-a', trace_path])
  if len(lcov_cmd) == 1:
    print("no trace files found, exiting...")
    return
  all_fuzz_file = os.path.join(coverage_dir, ALL_FUZZ_FILENAME)
  lcov_cmd.extend(['-o', all_fuzz_file])
  subprocess.check_call(lcov_cmd)

  if args.html_dir is None:
    return
  html_dir = os.path.abspath(args.html_dir)
  os.makedirs(html_dir, exist_ok=True)
  genhtml_cmd = [GENHTML, '-o', html_dir, all_fuzz_file]
  print("outputing html reports in {}".format(html_dir))
  subprocess.check_call(genhtml_cmd)





if __name__ == "__main__":
  parser = argparse.ArgumentParser(
    description="Full path to build directory, defaults to <vcc_root>/build"
  )
  parser.add_argument('--build-dir', '-d',
    type=str,
    help="path to build directory of Verify C Common",
    dest='build_dir',
    default=DEFAULT_BUILD_DIR)
  parser.add_argument('--html-dir', type=str, dest='html_dir',
    help="if provided, create html reports in specified directory",
    default=None)
  args = parser.parse_args()
  main(args)
