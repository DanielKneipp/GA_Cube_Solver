if (!exists("filename")) filename='default.dat'

set terminal pdf
set output filename.'_ind.pdf'

set grid
set key outside bottom center horizontal height 2

set yrange [0:]

set style data line

set title "Desempenho do GA"
set xlabel "Gerações"
set ylabel "Número de Indivíduos"

plot filename using 5 lw 2 title "Clones", \
           "" using 6 lw 2 title "Filhos melhores", \
           "" using 7 lw 2 title "Filhos piores"
