#!/usr/bin/env python

# El primer parametro es la cantidad maxima de planetas a dibujar
# la entrada debe ser por stdin, debe contener una linea listando los nombres de los planetas,
# y luego en cada linea las posiciones de los planetas en formato (x,y,z)
# ejemplo:
# sol tierra
# (0,0,0) (0,0,1)
# (0,0,0) (0,1,1)
#
# usage:
# cat posiciones_iniciales | ./simulador [dias [resolucion_de_simulacion [resolucion_de_grafico]]] | ./plot.py [max_planetas]

from sys import stdin,argv
from pylab import plot, show, axis, legend, annotate, savefig, Axes
from random import random

def anota(pnt,txt,color=(1.0, 0.7, 0.7)):
	annotate(txt, xy=pnt,  xycoords='data',xytext=(15, 0), textcoords='offset points',size=8,va="center",bbox=dict(boxstyle="round", fc=color, ec="none"), arrowprops=dict(arrowstyle="wedge,tail_width=.5", fc=color, ec="none",patchA=None, relpos=(0.2, 0.7), connectionstyle="arc3,rad=-0.1"))
	#annotate(txt, xy=pnt,  xycoords='data', xytext=(0, -45), textcoords='offset points', size=20, bbox=dict(boxstyle="round", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5)), arrowprops=dict(arrowstyle="wedge,tail_width=1.", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5),patchA=None, relpos=(0.2, 0.8), connectionstyle="arc3,rad=-0.1"))

cuerpos=stdin.readline().split()
N=min(len(cuerpos),len(argv)>1 and int(argv[1]) or len(cuerpos))
colors=[(.8,.8,.0),(1.,.2,.2),(.3,.8,.7),(.1,.7,.2),(.7,.7,.7),(.7,.0,.0),(.5,.5,.0),(.3,.3,.0)]+[(random(),random(),random()) for _ in range(N-8)]
posiciones=map(list,zip(*[map(eval,l.split()) for l in stdin.read().strip().split("\n")]))[:N]

for c in range(N):
	plot(*zip(*posiciones[c])[:2], label=cuerpos[c] , color=colors[c])
	plot(posiciones[c][-1][0],posiciones[c][-1][1], 'o', ms=8, color=colors[c], mew=0)
	anota(posiciones[c][-1][:2],cuerpos[c] ,colors[c])
#xs,ys=zip(*[posiciones[c][-1][:2] for c in N])
axis('scaled')
#legend(loc=0)
#savefig('planetas.png',dpi=1200/8.)
show()
