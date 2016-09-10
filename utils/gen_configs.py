from os.path import join

configs_out_path = 'configs'

NUM_INDIV = [100, 1000, 10000]
NUM_GENS = [100, 300, 600, 1200]
P_CROSS = [0, 0.4, 0.8, 1]
P_MUT = [0, 0.4, 0.8, 1]
TOURN_SIZE = [1, 2, 4, 8]
USE_ELIT = [0, 1]
NUM_ELITES = [0, 4, 12] # 0 to match with USE_ELIT = 0
N_CUT_POINTS = [0, 1, 3, 6, 10] # 0 to match with P_CROSS = 0
FLIP_MUT_GEN_PROB = [0, 0.02, 0.09, 0.15, 0.5] # 0 to match with NUM_GENS_WITH_FLIP = 0
NUM_GENS_WITH_FLIP = [0, 20, 80, 200]
INIT_POP_PROB_GENE_BE_NAM = [0, 0.4, 0.8, 1]
MUT_NAM_TO_END_PROB = [0, 0.5, 1]
CONFIG_NAME = 'c'

config_idx = 1

for n_i in NUM_INDIV:
    for n_g in NUM_GENS:
        for p_c in P_CROSS:
            for p_m in P_MUT:
                for t_s in TOURN_SIZE:
                    for u_e in USE_ELIT:
                        for n_e in NUM_ELITES:
                            for n_c_p in N_CUT_POINTS:
                                for f_m_g_p in FLIP_MUT_GEN_PROB:
                                    for n_g_w_f in NUM_GENS_WITH_FLIP:
                                        for i_p_p_g_b_n in INIT_POP_PROB_GENE_BE_NAM:
                                            for m_n_t_e_p in MUT_NAM_TO_END_PROB:

                                                #Removing some redundant and impracticable configurations
                                                if n_g_w_f > n_g:
                                                    continue

                                                if (u_e == 0 and n_e > 0 or
                                                    u_e == 1 and n_e == 0):
                                                    continue

                                                if (p_c == 0 and n_c_p > 0 or
                                                    p_c > 0 and n_c_p == 0):
                                                    continue

                                                if p_m == 0 and n_g_w_f > 0:
                                                    continue

                                                if p_m == 0 and m_n_t_e_p > 0:
                                                    continue

                                                if (n_g_w_f == 0 and f_m_g_p > 0 or
                                                    n_g_w_f > 0 and f_m_g_p == 0):
                                                    continue

                                                config_name = 'c' + str(config_idx)
                                                config_file_name = config_name + '.conf'
                                                with open(join(configs_out_path, config_file_name), 'x') as f:
                                                    f.write('NUM_INDIV: ' + str(n_i) + '\n')
                                                    f.write('NUM_GENS: ' + str(n_g) + '\n')
                                                    f.write('P_CROSS: ' + str(p_c) + '\n')
                                                    f.write('P_MUT: ' + str(p_m) + '\n')
                                                    f.write('TOURN_SIZE: ' + str(t_s) + '\n')
                                                    f.write('USE_ELIT: ' + str(u_e) + '\n')
                                                    f.write('NUM_ELITES: ' + str(n_e) + '\n')
                                                    f.write('N_CUT_POINTS: ' + str(n_c_p) + '\n')
                                                    f.write('FLIP_MUT_GEN_PROB: ' + str(f_m_g_p) + '\n')
                                                    f.write('NUM_GENS_WITH_FLIP: ' + str(n_g_w_f) + '\n')
                                                    f.write('INIT_POP_PROB_GENE_BE_NAM: ' + str(i_p_p_g_b_n) + '\n')
                                                    f.write('MUT_NAM_TO_END_PROB: ' + str(m_n_t_e_p) + '\n')
                                                    f.write('CONFIG_NAME: c' + str(config_idx) + '\n')

                                                config_idx = config_idx + 1
