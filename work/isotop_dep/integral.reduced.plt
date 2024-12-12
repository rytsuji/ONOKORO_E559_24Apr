set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,10"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:46]

#set ylabel 'TDX ratio t/^{3}He' font "Arial,15"
set ylabel 'ratio' font "Arial,15"
set ylabel 'reduced ratio  TDX ratio/n_{X} ratio  ^{3}He/t' font "Arial,15"
set yrange [0:2.0]
set ytics nomirror

#plot "integral.dat" u 1:(($4/$11)/($2/$10)/1.46):(($4/$11)/($2/$10)/1.46)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "TDX exp"

plot "integral.dat" u 1:(($4/$2)/($7/$6)/1.46):(($4/$2)/($7/$6)/1.46)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 4  lc rgb "blue" title "(TDX_{^{3}He}}/TDX_{t})_{exp}/(n_{^{3}He}/n_{t}) v1"
replot "integral.dat" u 1:(($4/$2)/($9/$8)/1.46):(($4/$2)/($9/$8)/1.46)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 9  lc rgb "green" title "(TDX_{^{3}He}}/TDX_{t})_{exp}/(n_{^{3}He}/n_{t}) v2"
replot "integral.dat" u 1:($11/$10) axis x1y1 pt 5  lc rgb "red" title "(TDX_{^{3}He}/TDX_{t})_{DWIA}"
#replot "integral.dat" u 1:($7/$6) axis x1y1 pt 5  lc rgb "blue" title "theory1"
#replot "integral.dat" u 1:($9/$8) axis x1y1 pt 6  lc rgb "green" title "theory2"
#plot "integral.dat" u 1:($7/$6) axis x1y1 pt 4  ps 2 lc rgb "blue" title "theory"#

#plot "integral.dat" u 1:(($4/$2)/($7/$6)/($11/$10)/1.46)**(-1):(($4/$2)/($7/$6)/($11/$10)/1.46)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 4  lc rgb "blue" title "v1"
#replot "integral.dat" u 1:(($4/$2)/($9/$8)/($11/$10)/1.46):(($4/$2)/($9/$8)/($11/$10)/1.46)*sqrt(($3/$2)**2+($5/$4)**2) axis x1y1 with yerrorbars pt 9  lc rgb "green" title "v2"





