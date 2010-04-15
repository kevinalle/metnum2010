#!/usr/bin/env python
from matplotlib.pyplot import *
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-o", "--out", dest="filename",help="Save PNG to file")
parser.add_option("-q", action="store_false", dest="show", default=True)
(options, args) = parser.parse_args()

ys=map(float,sys.stdin.read().split())
xs=range(len(ys))
plot(xs,ys,'k.',label=r"algoritmo")
xlabel("$n$")
ylabel("$x_n$")
p10=(max(ys)-min(ys))*.1
ylim(min(ys)-p10,max(ys)+p10)
xlim(-2,len(xs)+2)
legend(loc=0)
if options.filename: savefig(options.filename,dpi=640./8)
if options.show: show()
