set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'T_{p} (MeV)' font "Arial,18"
set xrange [140:160]

set ylabel ' TDX ({/Symbol m}b/MeV・str^2)' font "Arial,15"
set yrange [0:3.0]

plot "pph_40Ca.dat" u 1:($2*10):($3*10) with yerrorbars pt 9  lc rgb "blue" title "^{40}Ca({/Times-New-Roman:Italic p,ph}) 1/2+"

replot "pph_40Ca_gs.dat" u 1:($2*10):($3*10) with yerrorbars pt 9  lc rgb "red" title "^{40}Ca({/Times-New-Roman:Italic p,ph}) 3/2+"






