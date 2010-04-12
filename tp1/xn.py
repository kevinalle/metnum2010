#!/usr/bin/env python

from itertools import *

def alpha_beta_gamma(x0, x1):# gamma != 0
	mat = [ [ 3-xo  ,   5-x0,     100-x0        ],
			[ 3*(3-x1), 5*(5-x0), (100)*100-x0] ] ]
			
	triangular(mat)
	
	b = -mat[1][2]/mat[1][1]
	a = -mat[0][2]/mat[0][0] - b*mat[0][1]/mat[0][0]
	return a, b
		

def triangular(mat):
	n = len(mat)
	for i in xrange(0, n-1):
		#Hallar fila de mayor coeficiente
		coefs = [ l[i] for l in mat[i:n] ]
		idx = coefs.index(max(coefs))
		mat[i], mat[idx] = mat[idx], mat[i]
		#Pivotear con esa fila
		if mat[i][i] != 0:
			for k in xrange(i+1,n):
				mat[k][i:] = calc_fila(mat[i][i:], mat[k][i:])

	
def calc_fila(l1, l2):
	cte = float(l2[0])/float(l1[0])
	return [ y-x*cte for y, x in zip(l2,l1) ]


def x_n(n,x1,x0):
	if n == 0: return x0
	elif n == 1: return x1
	else:
		return 108 - (815 - (1500/x_n(n-2,x1,x0)))/x_n(n-1,x1,x0)
		
def x_n_iter(n,x1,x0):
	if n >= 1:
		res,res_1 = x1, x0
	else: res = x0
	
	for i in xrange(1,n):
		res += 108 - (815 - (1500/res_1))/res
		
	return res
		


def main():
	
	return 0

if __name__ == '__main__': main()
