set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'A' font "Arial,15"
set ylabel 'counts/h (1/2^{+})' font "Arial,15"
set xrange [38:50]
set yrange [0:6]
#plot "pph.dat" u 1:2:3 with yerrorbars
plot "pph.dat" u 1:2