set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x_{gfp}  (mm)' font "Arial,15"
set ylabel 't-(t|a)a-(t|a^2)a^2' font "Arial,15"

#f(x)=p0+p1*x+p2*x*x
#fit f(x) "tof_gr.dat" u 1:4 via p0,p1,p2
f(x)=p0+p1*x
fit f(x) "tof_gr.dat" u 1:4 via p0,p1

plot "tof_gr.dat" u 1:4

#set label 1 at graph 0.2,0.3 sprintf("{p0 = %e \n p1 = %e \n p2 = %e }", p0,p1,p2)
set label 1 at graph 0.2,0.3 sprintf("{p0 = %e \n p1 = %e}", p0,p1)
replot f(x)

set terminal 'png'
set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/gr_tof_x.png"
replot
