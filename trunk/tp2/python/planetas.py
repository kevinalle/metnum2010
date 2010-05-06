#!/usr/bin/env python

from numpy import matrix
from vectors import V3

class Cuerpo:
	def __init__(self,nombre,m=1,x0=V3(),v0=V3()):
		self.nombre=nombre;self.m=m;self.x0=x0;self.v0=v0;

cuerpos=[]
cuerpos.append(Cuerpo("tierra",1.,V3(0,0,0), V3(0,0,0)))
cuerpos.append(Cuerpo("luna", .01,V3(10,0,0),V3(0,2.3,0)))
N=len(cuerpos)
y=[c.v0 for c in cuerpos]+[c.x0 for c in cuerpos]
dt=.8
G=50

def F(i,j,xi,xj):
	return -G*cuerpos[i].m*cuerpos[j].m*(xi-xj)/(xi-xj).norm()**3

def f(y):
	return [sum([F(i,j,y[N+i],y[N+j])/cuerpos[i].m for j in range(N) if j!=i],V3()) for i in range(N)]+[y[i] for i in range(N)]


xt=[cuerpos[0].x0[0]];yt=[cuerpos[0].x0[1]];zt=[cuerpos[0].x0[2]]
xl=[cuerpos[1].x0[0]];yl=[cuerpos[1].x0[1]];zl=[cuerpos[1].x0[2]]
for _ in range(800):
	y=[a+dt*b for a,b in zip(y,f(y))]
	xt.append(y[N+0][0]);yt.append(y[N+0][1]);zt.append(y[N+0][2])
	xl.append(y[N+1][0]);yl.append(y[N+1][1]);zl.append(y[N+1][2])

#print zip(xt,yt)

import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = Axes3D(fig)
ax.plot(xt, yt, zt, c='b', label='tierra')
ax.plot(xl, yl, zl, c='k', label='luna')
ax.set_xlim3d(-20, 20)
ax.set_ylim3d(-20, 20)
ax.set_zlim3d(-20, 20)
ax.legend()
plt.show()

