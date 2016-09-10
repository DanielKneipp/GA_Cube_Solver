import glob
import sys
from os.path import join
import subprocess
from concurrent.futures import ThreadPoolExecutor

INSTANCE_FOLDER = 'instances'
CONFIG_FOLDER = 'configs'
OUTPUT_FOLDER = join('results', '')
EXEC = 'cube_ga_solver.exe'
NUM_EXECS = 1
NUM_THREADS = 4

instances = glob.glob(join(INSTANCE_FOLDER, 'in*'))
configs = glob.glob(join(CONFIG_FOLDER, '*.conf'))

def run_cmd(cmd, exec_n):
    print('Process ' + str(exec_n) + ' started! Command: ' + str(cmd))

    p = subprocess.run(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=True,
        universal_newlines=True
    )

    if p.stderr != '':
        return 'Process ' + str(exec_n) + ': STDERR: ' + p.stderr

    return 'Process ' + str(exec_n) + ': All fine'

def done_callback(future):
    print(future.result())

with ThreadPoolExecutor(max_workers=NUM_THREADS) as executor:
    n = 1
    for i in instances:
        for c in configs:
            args = [EXEC, i, c, OUTPUT_FOLDER, str(NUM_EXECS)]
            f = executor.submit(run_cmd, args, n).add_done_callback(done_callback)
            n = n + 1
