set title "^{12}C(p,p^{3}He) dk_{F}=20 MeV/c" font "Arial,20"

set xrange [45:60]
set yrange [40:65]

set xlabel 'GR angle (deg)' font "Arial,12"
set ylabel 'LAS angle  (deg)' font "Arial,12"

set object 4 rect from 50.2,47.5 to 51.5,54.3 fs empty border rgb "black" linewidth 3
plot "../dat/pph_12C.gated1.dat" u 2:3 title "E_{p}=146 MeV" pt 7 pointsize 0.2 #lc "blue"
replot "../dat/pph_12C.gated2.dat" u 2:3 title "E_{p}=147.5 MeV" pt 7 pointsize 0.2 #lc "blue"
replot "../dat/pph_12C.gated3.dat" u 2:3 title "E_{p}=149 MeV" pt 7 pointsize 0.2 #lc "blue"
replot "../dat/pph_12C.gated4.dat" u 2:3 title "E_{p}=150.5 MeV" pt 7 pointsize 0.2 #lc "blue"
replot "../dat/pph_12C.gated5.dat" u 2:3 title "E_{p}=152 MeV" pt 7 pointsize 0.2 #lc "blue"



set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/kinema_12C_pph.png"
replot


