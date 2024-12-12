f(x,y)=p00+p10*y+p20*(y**2)+p30+(y**3)+p40*(y**4)+p01*x+p11*x*y+p21*x*(y**2)+p31*x*(y**3)+p02*(x**2)+p12*y*(x**2)+p22*(y**2)*(x**2)+p03*(x**3)+p13*y*(x**3)+p04*(x**4)

splot "b_gr.dat" u 1:2:5											
fit f(x,y) "b_gr.dat" u 1:2:5 via p00,p10,p20,p30,p40,p01,p11,p21,p31,p02,p12,p22,p03,p13,p04
replot f(x,y)