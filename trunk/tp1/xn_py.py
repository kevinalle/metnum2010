#!/usr/bin/env python
import sys
x0,x1=tuple(map(float,sys.argv[1:3]))
n=int(sys.argv[3])
for i in range(n):
	temp = 108.-(815.-(1500./x0))/x1
	x0 = x1
	x1 = temp
	print "%.5f"%x1
