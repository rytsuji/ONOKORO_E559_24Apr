set lmargin 15
set rmargin 15
set tmargin 1
set bmargin 5

set key font"Arial,15"
set tics font"Arial,15"

set xlabel 'mass number A' font "Arial,18"
set xrange [38:50]

set ylabel ' TDX ({/Symbol m}b/MeV・str^2)' font "Arial,15"
set yrange [0:0.5]
set ytics nomirror

#set y2label '^{A}Ca({/Times-New-Roman:Italic p,ph}) TDX ({/Symbol m}b/str^{2}・MeV)' font "Arial,15"
#set y2range [0:2.9554200]
#set y2tics


plot "ppt_gs.dat" u 1:2:3 axis x1y1 with yerrorbars pt 9  lc rgb "blue" title "^{A}Ca({/Times-New-Roman:Italic p,pt})"
replot "pph_1st.dat" u 1:2:3 axis x1y1 with yerrorbars pt 4 lc rgb "red" title "^{A}Ca({/Times-New-Roman:Italic p,p}^{3}He)"





