#! /usr/bin/env python

import sys
from spline import spline
from cuadmin import cuadmin

def poli(coef,x):
	return sum(coef[i]*x**i for i in range(len(coef)))

def move(direccion):
	out.write("%d\n"%direccion)

def goto(gol):
	global arq,lastdir
	to=0
	if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2:
		arq+=step
		lastdir=1
		to=2
	elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1:
		arq-=step
		lastdir=-1
		to=1
	else:
		lastdir=0
		to=0
	move(to)

def metodo_spline2(ts,xs,ys):
	global arq,lastdir
	Sx=spline(zip(ts,xs))[-2]
	Sy=spline(zip(ts,ys))[-2]
	#plot([(poli(Sx[:-1],t-Sx[-1]),poli(Sy[:-1],t-Sy[-1])) for t in range(n+40)])

	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0 and t<200:
		t+=1
		yans=y
		y=poli(Sy[:-1],t-Sy[-1])
	gol=poli(Sx[:-1],t-Sx[-1]+y/(yans-y))
	goto(gol)

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
		cxa=cuadmin(ts,xs,min(6,len(ts)-1))
		cya=cuadmin(ts,ys,min(6,len(ts)-1))
		ts=ts[-6:]
		xs=[poli(cxa,t) for t in ts]
		ys=[poli(cya,t) for t in ts]
		
		cx=cuadmin(ts,xs,2)
		cy=cuadmin(ts,ys,2)
		xs=[poli(cx,t) for t in ts]
		ys=[poli(cy,t) for t in ts]

		metodo_spline2(ts,xs,ys)
		
		"""t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		goto(gol)"""
		
	elif len(ts)>1:
		cx=cuadmin(ts,xs,len(ts)-1)
		cy=cuadmin(ts,ys,len(ts)-1)
		t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		goto(gol)

	else: move(0)
		
