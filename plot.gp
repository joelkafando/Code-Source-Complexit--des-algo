set terminal pngcairo size 1200,800 enhanced font 'Arial,18'
set output 'complexite.png'
set title 'Courbe évolutive de la complexité des Algorithmes'
set xlabel "Taille de l'input (n)"
set ylabel 'Complexité relative'
set grid
set key left top
plot 'data.dat' using 1:2 with lines lw 3 lc rgb '#0072BD' title 'O(1)', \
     '' using 1:3 with lines lw 3 lc rgb '#EDB120' title 'O(n)', \
     '' using 1:4 with lines lw 3 lc rgb '#D95319' title 'O(n^2)'
