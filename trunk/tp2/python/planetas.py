#!/usr/bin/env python

from numpy import matrix
from vectors import V3
from random import random

class Cuerpo:
	def __init__(self,nombre,m=1,x0=V3(),v0=V3(),color=None,rad=.025):
		self.nombre=nombre;self.m=m;self.x0=x0;self.v0=v0;self.color=color or (random(),random(),random());self.rad=rad;

sol =		Cuerpo("Sol",    1.9891,        V3(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05),  V3(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08), (.8,.8,.0), 695500.)
tierra =	Cuerpo("Tierra", 0.0000059736,  V3(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05), V3(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07), (.1,.7,.2), 6378.)
luna =	Cuerpo("Luna", 0.00000007349,   V3(-7.248557601516714e-01, -7.039097848869444e-01, 1.029051462977911e-04), V3(1.220576787081027e-02, -1.211595432894550e-02, 4.775108508860639e-05), (.7,.7,.7), 1738.)
mercurio=Cuerpo("Mercurio", 0.0000003302,V3(-2.563687782457914E-01, -3.810998677594219E-01, -8.153193298845162E-03),V3(1.781451838572982E-02, -1.414097937982711E-02, -2.789632381177015E-03), (1.,.2,.2), 2440.)
venus =  Cuerpo("Venus", 0.0000048685,   V3(-2.745105890947935E-01, 6.675955871621595E-01, 2.473298509458710E-02),  V3(-1.880800003531344E-02, -7.736184882354628E-03, 9.795183384655537E-04), (.3,.8,.7), 6051.)
marte =  Cuerpo("Marte", 0.00000064185,  V3(-1.644799113455717E+00, 2.491823732968801E-01, 4.547552485947825E-02),  V3(-1.562104985945559E-03, -1.264976840237743E-02, -2.265804582138816E-04), (.7,.0,.0), 3397.)
jupiter =Cuerpo("Jupiter", 0.00189813,   V3(4.814383212086098E+00, -1.241505788193773E+00, -1.026521185883739E-01), V3(1.791829827597031E-03, 7.666882051378563E-03, -7.193518744890309E-05), (.5,.5,.0), 71492.)
saturno =Cuerpo("Saturno", 0.000568319,  V3(-9.498834472404264E+00, -4.314789953129710E-01, 3.854986365834464E-01), V3(-4.474247412442582E-05, -5.585253179574848E-03, 9.894753356331143E-05), (.3,.3,.0), 60268.)
cuerpos=[sol,luna,tierra,mercurio,venus,marte]#,jupiter,saturno]
n=len(cuerpos);N=xrange(n)
days=300
samples=8000
dt=float(days)/samples

y=[c.v0 for c in cuerpos]+[c.x0 for c in cuerpos]
G=0.0001488180711083514625549864281980165853856665309337938391

def F(i,j,xi,xj):
	return -G*cuerpos[i].m*cuerpos[j].m*(xi-xj)/(xi-xj).norm()**3

def f(y):
	return [sum([F(i,j,y[n+i],y[n+j]) for j in N if j!=i],V3())/cuerpos[i].m for i in N]+[y[i] for i in N]


posiciones=[[c.x0] for c in cuerpos]
for _ in range(samples):
	y=[a+dt*b for a,b in zip(y,f(y))]
	for i in N: posiciones[i].append(y[n+i])

# DRAW
def render_matplotlib():
	import matplotlib as mpl
	from mpl_toolkits.mplot3d import Axes3D
	import matplotlib.pyplot as plt

	fig = plt.figure()
	ax = Axes3D(fig)
	for c in N: ax.plot(*zip(*posiciones[c]), label=cuerpos[c].nombre)
	for c in N: ax.scatter(*map(lambda x:[x],posiciones[c][-1]),marker='s',s=2e80)
	xs,ys,zs=([],[],[])
	for c in N: xs+=zip(*posiciones[c])[0];ys+=zip(*posiciones[c])[1];zs+=zip(*posiciones[c])[2]
	maxrange=max(map(lambda ls:max(ls)-min(ls),[xs,ys,zs]))
	ax.set_xlim3d((max(xs)+min(xs)-maxrange)/2, (max(xs)+min(xs)+maxrange)/2)
	ax.set_ylim3d((max(ys)+min(ys)-maxrange)/2, (max(ys)+min(ys)+maxrange)/2)
	ax.set_zlim3d((max(zs)+min(zs)-maxrange)/2, (max(zs)+min(zs)+maxrange)/2)
	ax.legend()
	plt.show()

def render_mlab():
	import numpy
	import enthought.mayavi.mlab as mlab
	
	for c in N: mlab.plot3d(*zip(*posiciones[c]), tube_radius=cuerpos[c].rad)
	xs,ys,zs=zip(*zip(*posiciones)[-1])
	plan=mlab.points3d(xs,ys,zs,[10000.,6371.01,1737.53], color=(0,1,0), scale_factor=.00005)
	mlab.show()

def render_2d():
	from pylab import plot, show, axis, legend, annotate, savefig, Axes
	def anota(pnt,txt,color=(1.0, 0.7, 0.7)):
		annotate(txt, xy=pnt,  xycoords='data',xytext=(15, 0), textcoords='offset points',size=8,va="center",bbox=dict(boxstyle="round", fc=color, ec="none"), arrowprops=dict(arrowstyle="wedge,tail_width=.5", fc=color, ec="none",patchA=None, relpos=(0.2, 0.7), connectionstyle="arc3,rad=-0.1"))
		#annotate(txt, xy=pnt,  xycoords='data', xytext=(0, -45), textcoords='offset points', size=20, bbox=dict(boxstyle="round", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5)), arrowprops=dict(arrowstyle="wedge,tail_width=1.", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5),patchA=None, relpos=(0.2, 0.8), connectionstyle="arc3,rad=-0.1"))
	for c in N:
		plot(*zip(*posiciones[c])[:2], label=cuerpos[c].nombre, color=cuerpos[c].color)
		plot(posiciones[c][-1][0],posiciones[c][-1][1], 'o', ms=8, color=cuerpos[c].color, mew=0)
		anota(posiciones[c][-1][:2],cuerpos[c].nombre ,cuerpos[c].color)
	#xs,ys=zip(*[posiciones[c][-1][:2] for c in N])
	axis('scaled')
	#legend(loc=0)
	#savefig('planetas.png',dpi=1200/8.)
	show()

render_2d()
