set pm3d map

set lmargin 5
set rmargin 5
set tmargin 2
set bmargin 2

set xlabel "x variable" offset 0,0
set ylabel "y variable" offset -5,0

set title "^{12}Ca(p,p^{3}He) with ^{48}Ca setup  acceptance correction factor"
set title font"Arial,15"

set xlabel '|k_{F}|  (MeV/c)' font "Arial,12"
set ylabel '{/Symbol q}_{C.M} (deg)' font "Arial,12"

splot "../dat/pph_48Ca_12C.dat" u 1:2:3

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/acceptance_48Ca_12C_pph.png"
replot
