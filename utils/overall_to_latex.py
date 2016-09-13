from os.path import join
import glob

FILES_PATH = '.'

files = glob.glob(join(FILES_PATH, "*overall.txt"))

for file in files:
    out_file = file + '.latextable'
    with open(file, 'r') as f_obj:
        with open(out_file, 'a') as f_out_obj:
            f_out_obj.write('\\toprule \n')

            first_line = f_obj.readline()
            wrds = first_line.split()
            for wrd in wrds[:-1]:
                f_out_obj.write(wrd  + ' & ')
                

            f_out_obj.write(wrds[-1])
            f_out_obj.write(' \\\\ \n\\midrule \n')

            for line in f_obj:
                wrds = line.split()
                for wrd in wrds[:-1]:
                    f_out_obj.write(wrd  + ' & ')
                                            
                f_out_obj.write(wrds[-1])
                f_out_obj.write(' \\\\ \n')

            f_out_obj.write('\\bottomrule\n')