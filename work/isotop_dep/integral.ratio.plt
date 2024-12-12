set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,10"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

#set ylabel 'TDX ratio t/^{3}He' font "Arial,15"
set ylabel '^{3}He/t' font "Arial,15"
#set ylabel 'n_{^{3}He}/n_{t} theory' font "Arial,15"
set yrange [0:1.5]
set ytics nomirror


plot "integral.dat" u 1:($4/$2)/1.9173383:(($4/$2)/1.9173383*sqrt(($3/$2)**2+($5/$4)**2)) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "TDX_{^{3}He}/TDX_{t} exp"
#plot "integral.dat" u 1:($4/$2)/1.46:(($4/$2)/1.46*sqrt(($3/$2)**2+($5/$4)**2)) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "TDX_{^{3}He}/TDX_{t} exp"
replot "integral.dat" u 1:($7/$6) axis x1y1 pt 5  lc rgb "blue" title "n_{^{3}He}/n_{t} v1"
replot "integral.dat" u 1:($9/$8) axis x1y1 pt 6  lc rgb "green" title "n_{^{3}He}/n_{t} v2"









