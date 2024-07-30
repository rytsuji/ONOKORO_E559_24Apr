set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5
set xlabel 'x_{ldc}  (mm)' font "Arial,15"
set ylabel '(x_{lfp}|a^4_{ldc})' font "Arial,15"
f(x)=p0+p1*x+p2*x*x+p3*x*x*x
fit f(x) "fp_las_fit.dat" u 1:(-$5) via p0,p1,p2,p3
plot "fp_las_fit.dat" u 1:(-$5)
replot f(x)
set label 1 at graph 0.7,0.3 sprintf("{p0 = %e \n p1 = %e \n p2 = %e \n p3 = %e}", p0,p1,p2,p3)
set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/fp_las_p4.png"
replot

