
f(x,y)=D*(0.00001)*((x-X0)+A*100*(y-A0)+XA*(x-X0)*(y-A0)+(XXA*1000)*((x-X0)**2)*(y-A0)+AA*1000**((y-A0)**2)+XAA*(x-X0)*((y-A0)**2)+(XXAA*1000)*((x-X0)**2)*((y-A0)**2) )
D=-4.64226
A=1.15995
XA=-1.1893100
XXA=-0.89020199
AA=6.153
XAA=3.9534899
XXAA=8.5108900

fit f(x,y) "fp_gr.dat" u 2:3:1 via D,X0,A0,A,XA,XXA,AA,XAA,XXAA

#f(x,y)=D*((x-X0)+A*(y-A0)+XA*(x-X0)*(y-A0)+XXA*((x-X0)**2)*(y-A0)+AA*((y-A0)**2)+XAA*(x-X0)*((y-A0)**2)+XXAA*((x-X0)**2)*((y-A0)**2)+AAA*((y-A0)**3)+XAAA*(x-X0)*((y-A0)**3)+XXAAA*((x-X0)**2)*((y-A0)**3))
#fit f(x,y) "fp_gr.dat" u 2:3:1 via D,X0,A0,A,XA,XXA,AA,XAA,XXAA,AAA,XAAA,XXAAA



#f(x,y)=D*((x-X0)+A*(y-A0)+XA*(x-X0)*(y-A0)+XXA*((x-X0)**2)*(y-A0)+AA*((y-A0)**2)+XAA*(x-X0)*((y-A0)**2)+XXAA*((x-X0)**2)*((y-A0)**2)+AAA*((y-A0)**3)+XAAA*(x-X0)*((y-A0)**3)+XXAAA*((x-X0)**2)*((y-A0)**3) +XXXA*((x-X0)**3)*((y-A0)**1) +XXXA*((x-X0)**3)*((y-A0)**1) +XXXAA*((x-X0)**3)*((y-A0)**2)++XXXAAA*((x-X0)**3)*((y-A0)**3) +XXX*((x-X0)**3) )
#fit f(x,y) "fp_gr.dat" u 2:3:1 via D,X0,A0,A,XA,XXA,AA,XAA,XXAA,AAA,XAAA,XXAAA,XXXA,XXXAA,XXXAAA,XXX