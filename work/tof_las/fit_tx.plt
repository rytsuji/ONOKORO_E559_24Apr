set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x_{lfp}  (mm)' font "Arial,15"
set ylabel 'z' font "Arial,15"

f(x)=p0+p1*x

fit f(x) "fit/merge.dat" u 1:($2*0.17754523) via p0,p1
plot "fit/merge.dat" u 1:($2*0.17754523)

set label 1 at graph 0.2,0.3 sprintf("{ p0 = %e \n p1 = %e}", p0,p1)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/las_tof_x.png"
replot
