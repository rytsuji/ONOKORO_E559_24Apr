set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5
set xlabel 'x_{gdc}  (mm)' font "Arial,15"
set ylabel '(y_{fp}|b_{gtgt})' font "Arial,15"
plot "fit.dat" u 1:(1/$3) 
f(x)=1/(p0+p1*x)
p0=0.0016438662
p1=9.5832882e-07
fit f(x) "fit.dat" u 1:(1/$3) via p0,p1
set label 1 at graph 0.1,0.4 sprintf("{ (y|b) = %e \n  (y|b{/Symbol d})/D = %e }", p0,p1)
replot f(x)
set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/b_gr_p1.png"
replot


