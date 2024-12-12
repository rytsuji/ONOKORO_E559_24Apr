set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'A' font "Arial,15"
set ylabel 'counts/h (1/2^{+})' font "Arial,15"
set xrange [38:50]
set yrange [0:0.1]
plot "ppt.dat" u 1:($2/$4):(sqrt($3*$3+$2*$2*0.01)/$4) with yerrorbars
#plot "ppt.dat" u 1:2