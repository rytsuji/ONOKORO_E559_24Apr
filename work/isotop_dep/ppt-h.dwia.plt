set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]


set ylabel 'TDX_{exp} ({/Symbol m}b/MeV・str^2)' font "Arial,15"
set yrange [0:0.3]
set ytics nomirror

set y2label 'TDX_{DWIA} ({/Symbol m}b/MeV・str^2)' font "Arial,15"
set y2range [0:3.0]
set y2tics

plot "ppt.dat" u 1:($2):($3) axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "({/Times-New-Roman:Italic p,pt}) TDX_{exp}"
replot "pph.dat" u 1:($2):($3) axis x1y1 with yerrorbars pt 4 lc rgb "red" title "({/Times-New-Roman:Italic p,p}^{3}He) TDX_{exp}"


replot "ppt.dat" u 1:($4) axis x1y2 pt 9  lc rgb "green" title "({/Times-New-Roman:Italic p,pt}) TDX_{DWIA}"
replot "pph.dat" u 1:($4) axis x1y2 pt 4 lc rgb "orange" title "({/Times-New-Roman:Italic p,p}^{3}He) TDX_{DWIA}"

replot "ppt.dat" u 1:($4) axis x1y2 with line  lc rgb "green" notitle
replot "pph.dat" u 1:($4) axis x1y2 with line  lc rgb "orange" notitle









