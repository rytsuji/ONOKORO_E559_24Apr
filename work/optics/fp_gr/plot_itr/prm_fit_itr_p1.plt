set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5
set xlabel 'x_{gdc}  (mm)' font "Arial,15"
set ylabel '{/Symbol D}(x_{gdc}|a_{gdc})' font "Arial,15"

plot "~/work/art_analysis/e559_24apr/work/fp_gr/fit_itr/prm_itr.dat"  u 1:(-$2) title '{/Symbol D}(x_{gdc}|a_{gdc})'

f(x)=p0+p1*x+p2*x*x
fit f(x) "~/work/art_analysis/e559_24apr/work/fp_gr/fit_itr/prm_itr.dat" u 1:(-$2) via p0,p1,p2
set label 1 at graph 0.2,0.7 sprintf("{ p0 = %e \n p1 = %e \n p2 = %e }", p0,p1,p2)
replot f(x)

#set terminal 'png'
#set termoption enhanced
#set output "/home/tsuji/work/art_analysis/e559_24apr/figs/gnuplot/fp_gr_a1_itr.png"
#replot

