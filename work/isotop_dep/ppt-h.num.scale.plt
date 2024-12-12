set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel '{/Times-New-Roman: n}_{{/Times-New-Roman:Italic t}}' font "Arial,15"
set yrange [0:0.079760479]
set ytics nomirror
set ytics font "Arial,12"

set y2label '{/Times-New-Roman: n}_{^{3}He}' font "Arial,15"
set y2range [0:0.180]
set y2tics font "Arial,12"
set y2tics

plot "ppt.dat" u 1:($2/$4):($3/$4) axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "{/Times-New-Roman:Italic t}"
replot "pph.dat" u 1:($2/$4):($3/$4) axis x1y2 with yerrorbars pt 4 lc rgb "red" title "^{3}He)"






