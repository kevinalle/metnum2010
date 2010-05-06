from math import sqrt

class V3(tuple):
	def __new__(self,x=0,y=0,z=0):
		return tuple.__new__(self,(float(x),float(y),float(z)))
	def __add__(self,v): return V3(self[0]+v[0],self[1]+v[1],self[2]+v[2])
	def __sub__(self,v): return V3(self[0]-v[0],self[1]-v[1],self[2]-v[2])
	def __rmul__(self,n): return V3(self[0]*n,self[1]*n,self[2]*n)
	def __mul__(self,n): return V3(self[0]*n,self[1]*n,self[2]*n)
	def __div__(self,n): return V3(self[0]/n,self[1]/n,self[2]/n)
	def norm(self): return sqrt(self[0]**2+self[1]**2+self[2]**2)
