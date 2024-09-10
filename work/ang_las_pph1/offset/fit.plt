set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'b_{ltgt}  (rad)' font "Arial,15"
set ylabel 'y_{lfp} (mm)' font "Arial,15"
f(x)=p0+p1*x
fit f(x) "yb.dat" u 1:2:3 via p0,p1#,p2#,p3
plot "yb.dat" u 1:2:3 w e
set label 1 at graph 0.2,0.3 sprintf("{ p0 = %e \n p1 = %e }", p0,p1)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/yb_pph.png"
replot
