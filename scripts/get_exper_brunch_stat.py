import re
import csv
import argparse
from collections import defaultdict

def read_brunchstat_from_log(log_file_name):
  log_file = open(log_file_name, 'r')
  line = log_file.readline()
  data = defaultdict(list)
  cur_test = None
  while line:
    # look for next test
    new_test = re.search("Test: ", line)
    if new_test:
      span = new_test.span()
      test_name = line[span[1]:]
      # remove _unsat_test
      cur_test = test_name[:-12]
    elif line.startswith("BRUNCH_STAT"):
      stat = line.split()
      # stat_name = " ".join(stat[1:-1])
      stat_num = stat[-1]
      data[cur_test].append(stat_num)
    line = log_file.readline()

  log_file.close()
  return data

def write_brunchstat_into_csv(data, out_file):
  with open(out_file, 'w+', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow([
      "job_name",
      "result",
      "bmc.circ_sz",
      "bmc.dag_sz",
      "bmc_time",
      "bmc_solve_time",
      "cda_time", "gssa_time",
      "opsem_assert_time",
      "opsem_simp_time",
      "seahorn_total_time"])
    for k, v in data.items():
      writer.writerow([k, *v])

if __name__ == "__main__":
  parser = argparse.ArgumentParser(
        description='in and out files')
  parser.add_argument('logfile', type=str, help=".log file to read from")
  parser.add_argument('--outfile', '-o', type=str, default="brunch_stat.csv", help="ouput csv filename")
  args = parser.parse_args()
  data = read_brunchstat_from_log(args.logfile)
  write_brunchstat_into_csv(data, args.outfile)

