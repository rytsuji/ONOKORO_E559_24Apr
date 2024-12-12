set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel '{/Times-New-Roman: n}_{{/Times-New-Roman: X}} ({/Times-New-Roman: X}={/Times-New-Roman: t}, ^{3}He)' font "Arial,15"
set yrange [0:0.5]
set ytics nomirror



plot "ppt.dat" u 1:($2/$4):($3/$4) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "{/Times-New-Roman:Italic t}"
replot "pph.dat" u 1:($2/$4):($3/$4) axis x1y1 with yerrorbars pt 4 lc rgb "blue" title "^{3}He"





