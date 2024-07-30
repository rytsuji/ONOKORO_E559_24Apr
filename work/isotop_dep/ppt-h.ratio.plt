set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set tics font "Arial,50"
set key font"Arial,50"

set xlabel 'mass number A' font "Arial,15"
set xrange [38:50]



set ylabel '^{A}Ca({/Times-New-Roman:Italic p,pt/h}) TDX ration ' font "Arial,15"
set yrange [0:1.2798780]
set ytics nomirror

plot "ppt.dat" u 1:2:3 axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"

replot "pph.dat" u 1:2:3 axis x1y2 with yerrorbars pt 4 lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,ph})"





