set title "^{12}C(p,p^{3}He) with ^{48}Ca setup dk_{F}=20 MeV/c" font "Arial,20"

set xrange [45:60]
set yrange [40:65]

set xlabel 'GR angle (deg)' font "Arial,12"
set ylabel 'LAS angle  (deg)' font "Arial,12"

set object 4 rect from 49.7,45.9 to 51.3,52.7 fs empty border rgb "black" linewidth 3
plot "../dat/pph_48Ca_12C_neg.dat" u 2:3 title "E_{p}=136 MeV" pt 7 pointsize 0.2 lc "blue"
replot "../dat/pph_48Ca_12C_center.dat" u 2:3 title "E_{p}=141 MeV" pt 7 pointsize 0.2 lc "green"
replot "../dat/pph_48Ca_12C_pos.dat" u 2:3 title "E_{p}=146 MeV" pt 7 pointsize 0.2 lc "red"


set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/kinema_48Ca_pph_12C.png"
replot


