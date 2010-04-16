#!/usr/bin/env python
import sys
from decimal import *
getcontext().prec=2000
x0,x1=tuple(map(Decimal,sys.argv[1:3]))
n=int(sys.argv[3])
for i in range(n):
	temp = Decimal(108)-(Decimal(815)-(Decimal(1500)/x0))/x1
	x0 = x1
	x1 = temp
	print "%.5f"%x1
