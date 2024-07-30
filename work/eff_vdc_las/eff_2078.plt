set lmargin 15
set rmargin 5
set tmargin 1
set bmargin 5

set xlabel 'x (mm)' font "Arial,15"
set ylabel 'tracking eff' font "Arial,15"
plot "eff_2078.dat" u 1:2 w line title "xu"
replot "eff_2078.dat" u 1:3 w line title "xv"
replot "eff_2078.dat" u 1:4 w line title "uv"