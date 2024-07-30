set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x_{lfp}  (mm)' font "Arial,15"
set ylabel '(t|a_{lfp})' font "Arial,15"
f(x)=p0
fit f(x) "tof_las.dat" u 1:2 via p0
plot "tof_las.dat" u 1:2
set label 1 at graph 0.2,0.3 sprintf("{p0 = %e }", p0)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/gr_las_a.png"
replot
