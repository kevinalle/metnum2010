#! /usr/bin/python

e = 0.00001

def xn_exacto(x0,x1,n):
	# si gamma puede ser 0
	if abs((x1-8)*x0 + 15) < e:
		# elijo un b
		b = 1
		# calculo a
		a = b*(5-x0)/(x0-3)
		# calculo la sucesion hasta n
		return [ ( a*3**(i+1) + b*5**(i+1) ) / ( a*3**i + b*5**i ) for i in range(2,n) ]
	# si gamma != 0
	else:
		# calculo b/g
		bg = 50*(600-297*x1+x0*(91+2*x1)) / (15+x0*(x1-8))
		#calculo a/g
		ag = (10000-100*x0-bg*(x0-5)) / (x0-3)
		# calculo la sucesion hasta n
		return [ ( ag*3**(i+1) + bg*5**(i+1) + 100**(i+1) ) / ( ag*3**i + bg*5**i + 100**i ) for i in range(2,n) ]

print xn_exacto(4.,4.25,20)