plot "ppt.dat" u 1:2:3 with e title "^{12}C(p,pt)"
replot "pph.dat" u 1:2:3 with e title "^{12}C(p,p^{3}He)"

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'T_{p} MeV' font "Arial,18"
set xrange [144:155]

set ylabel ' TDX ({/Symbol m}b/MeV*str^2)' font "Arial,15"
set yrange [0:7.5]
set ytics nomirror