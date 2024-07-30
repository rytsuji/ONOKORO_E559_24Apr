set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5
set xlabel 'x_{gdc}  (mm)' font "Arial,15"
set ylabel '(x_{gfp}|a_{gdc})' font "Arial,15"
f(x)=p0+p1*x+p2*x*x+p3*x*x*x+p4*x*x*x*x
fit f(x) "fp_gr_fit.dat" u 1:(-$2) via p0,p1,p2,p3,p4
plot "fp_gr_fit.dat" u 1:(-$2) title "(x_{gfp}|a_{gdc})"
set label 1 at graph 0.2,0.3 sprintf("{p0 = %e \n p1 = %e \n p2 = %e \n p3 = %e \n p4 = %e}", p0,p1,p2,p3,p4)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/fp_gr_p1.png"
replot

