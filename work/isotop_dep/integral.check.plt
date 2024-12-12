# データサイズの取得
stats "integral.dat" using 1 nooutput
N = STATS_records   # データの行数

# 配列の宣言
array A[N]
array nt[N]
array nt_err[N]
array nh[N]
array nh_err[N]
array nt_nogate[N]
array nt_err_nogate[N]
array nh_nogate[N]
array nh_err_nogate[N]
array ratio[N]
array ratio_err[N]
array ratio_t[N]
array ratio_h[N]
array ratio_t_err[N]
array ratio_h_err[N]

# データの配列への保存
stats "integral.dat" using (A[$0+1] = $1, 0) nooutput
stats "integral.dat" using (nt[$0+1] = $2, 0) nooutput
stats "integral.dat" using (nt_err[$0+1] = $3, 0) nooutput
stats "integral.dat" using (nh[$0+1] = $4, 0) nooutput
stats "integral.dat" using (nh_err[$0+1] = $5, 0) nooutput

stats "integral_nogate.dat" using (nt_nogate[$0+1] = $2, 0) nooutput
stats "integral_nogate.dat" using (nt_err_nogate[$0+1] = $3, 0) nooutput
stats "integral_nogate.dat" using (nh_nogate[$0+1] = $4, 0) nooutput
stats "integral_nogate.dat" using (nh_err_nogate[$0+1] = $5, 0) nooutput


# 配列の内容の表示
do for [i=1:N]{
       ratio_t[i]=(nt_nogate[i]/nt[i])
       ratio_h[i]=(nh_nogate[i]/nh[i])
       ratio_t_err[i]=ratio_t[i]*sqrt((nt_err_nogate[i]/nt_nogate[i])**2+(nt_err[i]/nt[i])**2)
       ratio_h_err[i]=ratio_h[i]*sqrt((nh_err_nogate[i]/nh_nogate[i])**2+(nh_err[i]/nh[i])**2)       
       ratio[i]=(ratio_h[i]/ratio_t[i])
       ratio_err[i]=ratio[i]*(sqrt(ratio_t_err[i]/ratio_t[i])**2+(ratio_h_err[i]/ratio_h[i])**2)
       print ratio_h[i]
}


set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel 'nogate/with angular gate(scaled by ^{12}C data)' font "Arial,15"
set yrange [0.5:2.0]
set ytics nomirror

plot ratio using (A[$1]):(ratio_h[$1]):(ratio_h_err[$1]) axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "TDX_{(p,p^{3}He)}"
replot ratio using (A[$1]):(ratio_t[$1]):(ratio_t_err[$1]) axis x1y1 with yerrorbars pt 9  lc rgb "red" title "TDX_{(p,pt)}"
replot ratio using (A[$1]):(ratio[$1]):(ratio_err[$1]) axis x1y1 with yerrorbars pt 9  lc rgb "black" title "TDX_{(p,p^{3}He)}/TDX_{(p,pt)}"








