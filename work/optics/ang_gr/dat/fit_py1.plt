#f(x,y)=p00+p10*y+p20*(y**2)+p30*(y**3)*p01*x+p11*x*y+p21*x*(y**2)+p02*(x**2)+p12*y*(x**2)+p03*(x**3)
f(x,y)=p00+p10*y+p20*(y**2)+p01*x+p11*x*y+p21*x*(y**2)+p02*(x**2)+p12*y*(x**2)

splot "b_gr.dat" u 1:2:4											
#fit f(x,y) "b_gr.dat" u 1:2:4 via p00,p10,p20,p30,p21,p01,p11,p02,p12,p03
fit f(x,y) "b_gr.dat" u 1:2:4 via p00,p10,p20,p01,p11,p21,p02,p12
replot f(x,y)