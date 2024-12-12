set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set tics font "Arial,15"
set key font"Arial,15"

set xlabel 'gate' font "Arial,15"
set xrange [0:4]



set ylabel 'ratio ' font "Arial,15"
set yrange [0:1.0]
set ytics nomirror

plot "40Ca_ppt.dat" u 1:($2/$4):($2/$4)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 4  lc rgb "red" title "^{40}Ca({/Times-New-Roman:Italic p,pt})"
replot "40Ca_pph.dat" u 1:($2/$4):($2/$4)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "^{40}Ca({/Times-New-Roman:Italic p,ph})"







