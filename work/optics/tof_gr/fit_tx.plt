set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x_{gfp}  (mm)' font "Arial,15"
set ylabel 'Z offset' font "Arial,15"

f(x)=p0+p1*x
#fit f(x) "fit/merge.dat" u 1:(-$2/112.64047) via p0,p1
#plot "fit/merge.dat" u 1:(-$2/112.64047)
fit f(x) "fit/merge.dat" u 1:($2*0.17755607) via p0,p1
plot "fit/merge.dat" u 1:($2*0.17755607)

set label 1 at graph 0.2,0.3 sprintf("{ p0 = %e \n p1 = %e}", p0,p1)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/gr_tof_x.png"
replot
