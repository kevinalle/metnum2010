#!/usr/bin/env python

from numpy import matrix
from vectors import V3

class Cuerpo:
	def __init__(self,nombre,m=1,x0=V3(),v0=V3()):
		self.nombre=nombre;self.m=m;self.x0=x0;self.v0=v0;

"""cuerpos=[]
cuerpos.append(Cuerpo("Tierra",1.,V3(0,0,0), V3(0,0,1)))
cuerpos.append(Cuerpo("Luna", .01,V3(10,0,0),V3(0,2.3,0)))
cuerpos.append(Cuerpo("Sol", .1,V3(0,10,0),V3(0,0,0)))"""

sol =		Cuerpo("Sol",    1.9891,       V3(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05),  V3(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08))
tierra =	Cuerpo("Tierra", 0.0000059736, V3(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05), V3(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07))
luna =	Cuerpo("Luna", 0.00000007349,  V3(-7.248557601516714e-01, -7.039097848869444e-01, 1.029051462977911e-04), V3(1.220576787081027e-02, -1.211595432894550e-02, 4.775108508860639e-05))
cuerpos=[sol,tierra,luna]

N=len(cuerpos)
y=[c.v0 for c in cuerpos]+[c.x0 for c in cuerpos]
dt=.01
G=0.0002499215588275752801651213378056900054016

def F(i,j,xi,xj):
	return -G*cuerpos[i].m*cuerpos[j].m*(xi-xj)/(xi-xj).norm()**3

def f(y):
	return [sum([F(i,j,y[N+i],y[N+j])/cuerpos[i].m for j in range(N) if j!=i],V3()) for i in range(N)]+[y[i] for i in range(N)]


posiciones=[[c.x0] for c in cuerpos]
for _ in range(10000):
	y=[a+dt*b for a,b in zip(y,f(y))]
	for i in range(N): posiciones[i].append(y[N+i])

# DRAW
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
#import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = Axes3D(fig)
for c in range(N): ax.plot(*zip(*posiciones[c]), label=cuerpos[c].nombre)
xs,ys,zs=([],[],[])
for c in range(N): xs+=zip(*posiciones[c])[0];ys+=zip(*posiciones[c])[1];zs+=zip(*posiciones[c])[2]
maxrange=max(map(lambda ls:max(ls)-min(ls),[xs,ys,zs]))
ax.set_xlim3d(min(xs), min(xs)+maxrange)
ax.set_ylim3d(min(ys), min(ys)+maxrange)
ax.set_zlim3d(min(zs), min(zs)+maxrange)
ax.legend()
plt.show()

