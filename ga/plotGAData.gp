if (!exists("filename")) filename='default.dat'

set terminal pdf
set output filename.'.pdf'

set grid
set key box

set yrange [0:]

set style data linespoints

set title "Desempenho do GA"
set xlabel "Gerações"
set ylabel "Fitness"

plot filename using 1 title "Máximo", \
           "" using 2 title "Mínimo", \
           "" using 3 title "Média"
