set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5
set xlabel 'x_{gdc}  (mm)' font "Arial,15"
set ylabel 'a_{gtgt}^{0}' font "Arial,15"
plot "fit.dat" u 1:2 #title "(x_{gfp}|a_{gdc})" 
f(x)=p0+p1*x
fit f(x) "fit.dat" u 1:2 via p0,p1
set label 1 at graph 0.1,0.4 sprintf("{ p0 = %e \n p1 = %e }", p0,p1)
replot f(x)
set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/a_gr_p0.png"
replot


