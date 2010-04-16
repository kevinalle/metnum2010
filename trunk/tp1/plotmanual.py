#!/usr/bin/env python
from matplotlib.pyplot import *

def xn_exacto(x0,x1,n):
	e=.00001
	# si gamma puede ser 0
	if abs((x1-8.)*x0 + 15.) < e:
		# elijo un b
		b = 1.
		# calculo a
		a = b*(5.-x0)/(x0-3.)
		# calculo la sucesion hasta n
		return ( a*3.**(n+1) + b*5.**(n+1) ) / ( a*3.**n + b*5.**n )
	# si gamma != 0
	else:
		# calculo b/g
		bg = 50.*(600.-297.*x1+x0*(91.+2.*x1)) / (15.+x0*(x1-8.))
		#calculo a/g
		ag = (10000.-100.*x0-bg*(x0-5.)) / (x0-3.)
		# calculo la sucesion hasta n
		return ( ag*3.**(n+1) + bg*5.**(n+1) + 100.**(n+1) ) / ( ag*3.**n + bg*5.**n + 100.**n )

x0,x1=4.,4.25
floats =[4.47059,4.64474,4.77053,4.85545,4.90575,4.84165,2.8218,-71.0303,111.99 ,100.534,100.027,100.001,100,100,100,100,100,100,100,100]
doubles=[4.47059,4.64474,4.77054,4.8557 ,4.91085,4.94554,4.96696,4.98005,4.98798,4.99284,4.9971 ,5.02619,5.57149,15.2844,72.2923,98.0839,99.9023,99.9951,99.9998,100]
python =[4.47059,4.64474,4.77054,4.85570,4.91085,4.94554,4.96696,4.98004,4.98791,4.99136,4.96746,4.42969,-7.81724,168.93917,102.03996,100.09995,100.00499,100.00025,100.00001,100.00000]
spreadsheet=[4.47059,4.64474,4.77054,4.85570,4.91085,4.94554,4.96696,4.98004,4.98791,4.99136,4.96746,4.42969,-7.81724,168.93917,102.03996,100.09995,100.00499,100.00025,100.00001,100.00000]
xs=range(2,len(floats)+2)
exactos=[xn_exacto(x0,x1,n) for n in xs]
plot(xs,exactos,'g-',label=r"exacto")
plot(xs,floats,'k-',label=r"C++ float")
plot(xs,doubles,'b-',label=r"C++ double")
plot(xs,python,'r--',label=r"Python")
plot(xs,spreadsheet,'k:',label=r"Spreadsheet")
xlabel("$n$")
ylabel("$x_n$")
xlim(0,len(xs)+2)
legend(loc=0)
savefig("informe/fig_comparaciones.png",dpi=640./8)
show()
