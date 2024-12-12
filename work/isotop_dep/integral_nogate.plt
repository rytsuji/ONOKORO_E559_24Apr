set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel 'TDX integrated by S_{X} ({/Symbol m}b/str^2)' font "Arial,15"
set yrange [0:5.0]
set ytics nomirror


#plot "integral.dat" u 1:2:($3) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
#replot "pph.dat" u 1:2:($3) axis x1y1 with yerrorbars pt 4 lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"
plot "integral_nogate.dat" u 1:($2*5) axis x1y1 pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
replot "integral_nogate.dat" u 1:($3*5) axis x1y1 pt 4  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"




