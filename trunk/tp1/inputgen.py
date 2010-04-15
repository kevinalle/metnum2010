#! /usr/bin/python

e = 0.00001

def exacto(x0,x1):
	# si gamma puede ser 0
	if (x1-8)*x0 + 15 < e:
		# si b==0 y a!=0
		if x0==3 and x1==3:
			return 3
		# si b!=0
		else:
			return 5
	# si gamma !=0
	else:
		return 100
	
		

def generate(min,max,gran):
	r = [float(i)/float(gran) for i in range(min*gran,max*gran+1)]
	for x0 in r:
		for x1 in r:
			print str(x0) + ", " + str(x1) + ", " + str(exacto(x0,x1))

generate(-10,10,10)
