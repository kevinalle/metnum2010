#!/usr/bin/env python
from matplotlib.pyplot import *
import sys
from optparse import OptionParser
import subprocess


parser = OptionParser()
parser.add_option("-c", "--compare", dest="x0x1",help="Compare to exact result")
parser.add_option("-o", "--out", dest="filename",help="Save PNG to file")
parser.add_option("-t", "--title", dest="title",help="Titulo del Grafico")
parser.add_option("-q", action="store_false", dest="show", default=True, help="Don't show output")
(options, args) = parser.parse_args()

def xn_exacto(x0,x1,n):
	e=.00001
	# si gamma puede ser 0
	if abs((x1-8.)*x0 + 15.) < e:
		# elijo un b
		b = 1.
		# calculo a
		a = b*(5.-x0)/(x0-3.)
		# calculo la sucesion hasta n
		return ( a*3.**(n+1) + b*5.**(n+1) ) / ( a*3.**n + b*5.**n )
	# si gamma != 0
	else:
		# calculo b/g
		bg = 50.*(600.-297.*x1+x0*(91.+2.*x1)) / (15.+x0*(x1-8.))
		#calculo a/g
		ag = (10000.-100.*x0-bg*(x0-5.)) / (x0-3.)
		# calculo la sucesion hasta n
		return ( ag*3.**(n+1) + bg*5.**(n+1) + 100.**(n+1) ) / ( ag*3.**n + bg*5.**n + 100.**n )

#def run(ejecutable,args):
#	fp=subprocess.Popen([ejecutable]+args, shell=False, stdin=subprocess.PIPE,stdout=subprocess.PIPE)
#	return fp.stdout.read()

ys=map(float,sys.stdin.read().split())
xs=range(2,len(ys)+2)
if options.x0x1:
	x0,x1=tuple(map(float,options.x0x1.split(",")))
	exactos=[xn_exacto(x0,x1,n) for n in xs]
	plot(xs,exactos,'g.',label=r"exacto")
plot(xs,ys,'kx',label=r"algoritmo")
xlabel("$n$")
ylabel("$x_n$")
p10=(max(ys)-min(ys))*.1
#ylim(min(ys)-p10,max(ys)+p10)
xlim(0,len(xs)+2)
legend(loc=0)
if options.title: title(options.title)
if options.filename: savefig(options.filename,dpi=640./8)
if options.show: show()
