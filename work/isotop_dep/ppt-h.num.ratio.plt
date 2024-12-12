set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel 'n_{^{3}He}/n_{t}' font "Arial,15"
set yrange [0:5]
set ytics nomirror
set arrow from  38,1.46 to 50,1.46 nohead lw 2 dt (10,5) lc rgb "black"
set label 1 at first   39,1.2 "^{12}C {/Symbol s}_t/{/Symbol s}_{^{3}He}" font "Arial,15"

plot "ppt-h.dat" u 1:(($5/$7)/($2/$4)):(sqrt( ($3*($5/$7)/(($2/$4)**2))**2+ ($6/($2/$4))**2 )) axis x1y1 with yerrorbars pt 9  lc rgb "red" notitle 








