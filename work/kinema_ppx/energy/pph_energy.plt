set title "(p,ph)" font "Arial,20"

set xrange [130:150]
set yrange [35:65]

set xlabel 'GR energy (MeV)' font "Arial,12"
set ylabel 'LAS energy (MeV)' font "Arial,12"

set object 1 rect from 136,43 to 146,60 fs empty border rgb "black"
plot -x+226-20 title "S_{X}=20.0 (MeV)"
replot -x+226-22.5 title "S_{X}=22.5 (MeV)"
replot -x+226-25.0 title "S_{X}=25.0 (MeV)"
replot -x+226-27.5 title "S_{X}=27.5 (MeV)"
replot -x+226-30.0 title "S_{X}=30.0 (MeV)"

#replot -x+226-26.366 title "S_{X}=26.36 (MeV), ^{40}Ca"


#set terminal 'png'
#set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/kinema_12C_ppt.png"
#replot
