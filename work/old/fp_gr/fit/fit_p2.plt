set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x_{gdc}  (mm)' font "Arial,20"
set ylabel '(x_{gfp}|a^2_{gdc})' font "Arial,20"
f(x)=p0+p1*x+p2*x*x+p3*x*x*x
fit f(x) "fp_gr_fit.dat" u 1:(-$3) via p0,p1,p2,p3
plot "fp_gr_fit.dat" u 1:(-$3)
set label 1 at graph 0.2,0.3 sprintf("{p0 = %e \n p1 = %e \n p2 = %e \n p3 = %e}", p0,p1,p2,p3)
replot f(x)


set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/fp_gr_p2.png"
replot

