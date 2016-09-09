if (!exists("filename")) filename='default.dat'

set terminal pdf
set output filename.'_fit.pdf'

set grid
set key outside bottom center horizontal height 2

set yrange [0:]

set style data line

set title "Desempenho do GA"
set xlabel "Gerações"
set ylabel "Fitness"

plot filename using 1 lw 2 title "Máximo", \
           "" using 2 lw 2 title "Mínimo", \
           "" using 3 lw 2 title "Média", \
           "" using 4 lw 2 title "Desvio padrão"
