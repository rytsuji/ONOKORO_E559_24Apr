#scale with 12C
set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,10"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel 'TDX integrated by S_{X} ({/Symbol m}b/sr^2)' font "Arial,15"
set yrange [0:1.2]
set ytics nomirror

set y2label 'number of clusters' font "Arial,15"
set y2range [0:0.17838288]
set y2tics nomirror


#plot "integral.dat" u 1:2:($3) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
#replot "pph.dat" u 1:2:($3) axis x1y1 with yerrorbars pt 4 lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"
#plot "integral.dat" u 1:($2*5) axis x1y1 pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
#replot "integral.dat" u 1:($3*5) axis x1y1 pt 4  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"

#plot "integral.dat" u 1:($2*1.46):($3*1.46) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
#replot "integral.dat" u 1:($4*1):($5*1) axis x1y1 with yerrorbars pt 4  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"
plot "integral.dat" u 1:($2*1.46):(sqrt(($3*1.46)**2+(0.1*$2)**2)) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
replot "integral.dat" u 1:($4*1.0):(sqrt(($5*1.0)**2+(0.1*$4)**2)) axis x1y1 with yerrorbars pt 4  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"
replot "integral.dat" u 1:($6) axis x1y2 pt 7  lc rgb "light-magenta" notitle 
replot "integral.dat" u 1:($6) axis x1y2 with line lc rgb "light-magenta" title "n_{t} theory v1"
replot "integral.dat" u 1:($7) axis x1y2 pt 7 lc rgb "cyan" notitle
replot "integral.dat" u 1:($7) axis x1y2 with line lc rgb "cyan" title "n_{^{3}He} theory1"

replot "integral.dat" u 1:($8*0.54388803) axis x1y2 pt 6  lc rgb "orange" notitle
replot "integral.dat" u 1:($8*0.54388803) axis x1y2 with line dt (10,5) lc rgb "orange" title "n_{t} theory v2"
replot "integral.dat" u 1:($9*0.54388803) axis x1y2 pt 6 lc rgb "green" notitle
replot "integral.dat" u 1:($9*0.54388803) axis x1y2 with line dt (10,5) lc rgb "green" title "n_{^{3}He} theory v2"



