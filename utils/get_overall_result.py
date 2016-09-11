import glob
import re
import numpy as np
from os.path import join, basename, exists
from os import makedirs

CUBESOLS_PATH = 'results'
OVERALL_PATH = join('results', 'overall')

def fix_minus_1(number): # number-1
    return number.split('-1')[0]

if not exists(OVERALL_PATH):
    makedirs(OVERALL_PATH)

files = glob.glob(join(CUBESOLS_PATH, '*.cubesols'))
pattern = re.compile(r'(_\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2}.log.cubesols)')
inst_name_patt = re.compile(r'in_test_\d_\d')
data = {}

for f in files:
    date = pattern.search(f)
    name = basename(f).replace(date.group(0), '')
    instance_name = inst_name_patt.search(name).group(0)
    config_name = name.replace(instance_name, '')[1:]

    if instance_name not in data:
        data[instance_name] = {config_name: {'fitness': []}}
    elif config_name not in data[instance_name]:
        data[instance_name][config_name] = {'fitness': []}

    with open(f, 'r') as f_obj:
        line = f_obj.readline()

        count_wrd = 0
        fit = 0

        for wrd in line.split():
            count_wrd = count_wrd + 1
            if count_wrd == 2:
                fit = float(fix_minus_1(wrd))
                data[instance_name][config_name]['fitness'].append(fit)
                break

for instance_name in data:
    file_out = instance_name + '_overall.txt'
    with open(join(OVERALL_PATH, file_out), 'x') as f_obj:
        f_obj.write('Config_Name Best Worst Mean Std\n')
        for config_name in data[instance_name]:
            best = str(min(data[instance_name][config_name]['fitness']))
            worst = str(max(data[instance_name][config_name]['fitness']))
            mean = str(np.mean(data[instance_name][config_name]['fitness']))
            std = str(np.std(data[instance_name][config_name]['fitness']))
            f_obj.write(config_name + ' ' + best + ' ' + worst + ' '  + mean + ' ' + std + '\n' )
