#! /usr/bin/env python

import sys
from spline import spline
from cuadmin import cuadmin

def poli(coef,x):
	return sum(coef[i]*x**i for i in range(len(coef)))

fin=open(sys.argv[1]).read()
out=open(sys.argv[2],'w')

data=map(lambda x: map(lambda y: float(y) if '.' in y else int(y),x.split()),fin.split("\n")[:-1])
pnts=[]
step=.05
arq=0.
lastdir=0

for i in range(1,data[0][0]): out.write("%d 0\n"%i)
for n in range(data[0][0],data[-1][0]+1):
	if data[0][0]<=n: pnts.append(data.pop(0))
	ts,xs,ys=zip(*pnts)
	out.write("%d "%n)
	
	if len(ts)>=4:
		cxa=cuadmin(ts,xs,8)
		cya=cuadmin(ts,ys,8)
		xs=[poli(cxa,t) for t in ts]
		ys=[poli(cya,t) for t in ts]
	
		cx=cuadmin(ts[-6:],xs[-6:],2)
		cy=cuadmin(ts[-6:],ys[-6:],2)
	
		t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2:
			arq+=step
			lastdir=1
			out.write("2\n")
		elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1:
			arq-=step
			lastdir=-1
			out.write("1\n")
		else:
			lastdir=0
			out.write("0\n")
	elif len(ts)>1:
		cx=cuadmin(ts,xs,1)
		cy=cuadmin(ts,ys,1)
		t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2:
			arq+=step
			lastdir=1
			out.write("2\n")
		elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1:
			arq-=step
			lastdir=-1
			out.write("1\n")
		else:
			lastdir=0
			out.write("0\n")
	else: out.write("0\n")
		
