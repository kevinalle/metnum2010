#!/usr/bin/env python

from itertools import *

def alpha_beta(x0, x1):# gamma == 0
	mat = [ [ , 0], [ , 0] ]
	triangular(mat)
	
		

# Precondicion: mat es cuadrada
def triangular(mat):
	n = len(mat)
	for i in xrange(0, n-1):
		#Hallar fila de mayor coeficiente
		coefs = [ l[i] for l in mat[i:n] ]
		idx = coefs.index(max(coefs))
		mat[i], mat[idx] = mat[idx], mat[i]
		#Pivoteaer con es fila
		if mat[i][i] != 0:
			for k in xrange(i+1,n):
				mat[k][i:n] = calc_fila(mat[i][i:n], mat[k][i:n])

	
def calc_fila(l1, l2):
	cte = float(l2[0])/float(l1[0])
	return [ y-x*cte for y, x in zip(l2,l1) ]


def x_n(n,x1,x0):
	if n == 0: return x0
	elif n == 1: return x1
	else:
		return 108 - (815 - (1500/x_n(n-2,x1,x0)))/x_n(n-1,x1,x0)
		


def main():
	
	return 0

if __name__ == '__main__': main()
