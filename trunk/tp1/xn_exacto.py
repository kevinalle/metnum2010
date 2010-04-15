#! /usr/bin/python

e = 0.00001

def pow(n,m):
	if m==0: return 1
	if m==1: return n
	else:
		return n*pow(n,m-1)

def xn_exacto(x0,x1,n):
	# si gamma puede ser 0
	if (x1-8)*x0 + 15 < e:
		# elijo un b
		b = 1
		# calculo a
		a = b*(5-x0)/(x0-3)
		# calculo la sucesion hasta n
		return [ ( a*pow(3,i+1) + b*pow(5,i+1) ) / ( a*pow(3,i) + b*pow(5,i) ) for i in range(2,n) ]
	# si gamma != 0
	else:
		# calculo b/g
		bg = 50*(600-297*x1+x0*(91+2*x1)) / (15+x0*(x1-8))
		#calculo a/g
		ag = (10000-100*x0-bg*(x0-5)) / (x0-3)
		# calculo la sucesion hasta n
		return [ ( ag*pow(3,i+1) + bg*pow(5,i+1) + pow(100,i+1) ) / ( ag*pow(3,i) + bg*pow(5,i) + pow(100,i) ) for i in range(2,n) ]
