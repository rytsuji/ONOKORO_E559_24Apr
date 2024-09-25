set title "^{40}Ca(p,pt) dk_{F}=20 MeV/c" font "Arial,20"

set xrange [45:60]
set yrange [40:65]

set xlabel 'GR angle (deg)' font "Arial,12"
set ylabel 'LAS angle  (deg)' font "Arial,12"

set object 4 rect from 50.7,48.2 to 52.2,53.2 fs empty border rgb "black" linewidth 3
plot "../dat/ppt_40Ca_neg.gated.dat" u 2:3 title "E_{p}=145 MeV" pt 7 pointsize 0.2 lc "blue"
replot "../dat/ppt_40Ca_center.gated.dat" u 2:3 title "E_{p}=149 MeV" pt 7 pointsize 0.2 lc "green"
replot "../dat/ppt_40Ca_pos.gated.dat" u 2:3 title "E_{p}=153 MeV" pt 7 pointsize 0.2 lc "red"


set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/kinema_40Ca_ppt.gated.png"
replot


