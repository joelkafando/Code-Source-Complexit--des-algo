set terminal pngcairo size 1200,800 enhanced font 'Arial,18'
set output 'complexite.png'
set title 'Courbe évolutive de la complexité des Algorithmes'
set xlabel "Taille de l'input (n)"
set ylabel 'Complexité'
set grid
set key left top
set xrange [1:14]
set yrange [0:14]
set xtics 1
set ytics 1
plot 'data.dat' using 1:2 with lines lw 3 lc rgb '#0072BD' title 'O(1) - Constant', \
     '' using 1:3 with lines lw 3 lc rgb '#EDB120' title 'O(n) - Linéaire', \
     '' using 1:4 with lines lw 3 lc rgb '#D95319' title 'O(2^n) - Exponentielle', \
     '' using 1:5 with lines lw 3 lc rgb '#7E2F8E' title 'O(n!) - Factorielle'
