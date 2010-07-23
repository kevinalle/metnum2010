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
from pylab import plot, show, axis, legend, annotate, savefig, Axes, axes
from random import random
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-o", "--out", dest="filename", help="Save PNG to file")
parser.add_option("-q", action="store_false", dest="show", default=True, help="Don't show output")
parser.add_option("-z", "--zoom", dest="zoom", default="all", help="Zoom del plot (ancho, en AU)")
parser.add_option("-c", "--center", type="int", dest="center", default=0, help="Cuerpo para centrar zoom (-1 es el ultimo)")
parser.add_option("-t", "--title", dest="title",help="Titulo del Grafico")
parser.add_option("-n", "--sinnombres", action="store_false", default=True, dest="nombres", help="Poner labels a los planetas")
parser.add_option("-r", "--relative", dest="relative_object", default=-1, help="Dibujar las trayectorias relativas a un planeta")
(options, args) = parser.parse_args()

def anota(pnt,txt,color=(1.0, 0.7, 0.7)):
        annotate(txt, xy=pnt,  xycoords='data',xytext=(15, 0), textcoords='offset points',size=8,va="center",bbox=dict(boxstyle="round", fc=color, ec="none"), arrowprops=dict(arrowstyle="wedge,tail_width=.5", fc=color, ec="none",patchA=None, relpos=(0.2, 0.7), connectionstyle="arc3,rad=-0.1"))
        #annotate(txt, xy=pnt,  xycoords='data', xytext=(0, -45), textcoords='offset points', size=20, bbox=dict(boxstyle="round", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5)), arrowprops=dict(arrowstyle="wedge,tail_width=1.", fc=(1.0, 0.7, 0.7), ec=(1., .5, .5),patchA=None, relpos=(0.2, 0.8), connectionstyle="arc3,rad=-0.1"))

def find(f, seq):
	"""Return index of first item in sequence where f(item) == True."""
	for num,item in enumerate(seq):
		if f(item): return num
	return -1

cuerpos=stdin.readline().split()
N=len(cuerpos)#min(len(cuerpos),len(argv)>1 and int(argv[1]) or len(cuerpos))
colors=[(.8,.8,.0),(1.,.2,.2),(.3,.8,.7),(.1,.7,.2),(.7,.7,.7),(.7,.0,.0),(.5,.5,.0),(.3,.3,.0)]+[(random(),random(),random()) for _ in range(N-8)]
posiciones=map(list,zip(*[map(eval,l.split()) for l in stdin.read().strip().split("\n")]))[:N]

#print posiciones

#relative_object=find(lambda x:'*' in x, cuerpos)
relative_object=int(options.relative_object)

if relative_object>=0:
	#relativizo las posiciones
	for c in range(N):
		if c!=relative_object:
			for i in range(len(posiciones[c])):
				posiciones[c][i]=[posiciones[c][i][pos]-posiciones[relative_object][i][pos] for pos in (0,1,2)]
	posiciones[relative_object]=[(0,0,0) for _ in range(len(posiciones[relative_object]))] 

for c in range(N):
	plot(*zip(*posiciones[c])[:2], label=cuerpos[c] , color=colors[c])
	plot(posiciones[c][-1][0],posiciones[c][-1][1], 'o', ms=6, color=colors[c], mew=0)
	if options.nombres: anota(posiciones[c][-1][:2],cuerpos[c] ,colors[c]) #nombres de los planetas

axes().set_aspect(1.)
#axis([-1.2,1.2,-1.2,1.2], aspect='scaled') # ver solo el centro

(misilx,misily)=(posiciones[options.center][-1][0],posiciones[options.center][-1][1])
if options.zoom!="all":
	z=float(options.zoom)
	axis([misilx-z/2.,misilx+z/2.,misily-z/2.,misily+z/2.], aspect='scaled') # ver el misil

if options.title: title(options.title)
#legend(loc=0)
if options.filename: savefig(options.filename+'.png',dpi=1200/8.)
if options.show: show()
