#!/usr/bin/python3
"""
This script looks at a base yaml config file and a job specific config file.
1. It first reads all the flags in the base
2. It then adds-to/updates the base config with the job specific config
"""
import argparse
import logging
import os
from typing import Dict
import yaml
import pdb

VERIFY_OPTIONS = 'verify_options'

def file_path(path: str) -> str:
    """This function ensures that the given path exists and is a file"""
    if os.path.isfile(path):
        return os.path.abspath(path)
    else:
        raise argparse.ArgumentTypeError(f"readable_file:{path} is not a valid path")

def read_yaml_file(path: str) -> Dict[str, str]:
    """Read yaml file and create a dictionary of flags.

       Return empty dict if required data is not found in yaml file.
    """
    with open(path) as f:
        data = yaml.load(f, Loader=yaml.SafeLoader)
        if not data:
            logging.warning('%s could not be loaded'.format(path))
            return {}
        return {} if (VERIFY_OPTIONS not in data or not data[VERIFY_OPTIONS]) else data[VERIFY_OPTIONS]
        
def update_dict(original: Dict[str, str], update: Dict[str, str] ) -> Dict[str, str]:
    """Update the original dictionary of flags with the job specific one."""
    original.update(update)
    return original

def create_flag(key: str, val: str) -> str:
    if val == 'True' or val == 'False':
        val = val.lower()
    elif isinstance(val, bool):
        val = str(val).lower()	

    return '--{0}'.format(key) if val == '' else '--{0}={1}'.format(key, val)

def create_cmd_line(flag_dict: Dict[str, str]) -> str:
    """Create a cmd line string from a dictionary of flags."""
    args_list = [create_flag(k, flag_dict[k]) for k in flag_dict.keys()]
    return ' '.join(args_list)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--base_config', type=file_path, required=True)
    parser.add_argument('--job_config', type=file_path, required=True)
    args = parser.parse_args()
    print(create_cmd_line(update_dict(read_yaml_file(args.base_config),
                                      read_yaml_file(args.job_config))))

if __name__ == '__main__':
    main()
