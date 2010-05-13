class matrix(list):
	def __init__(self, n,m=None,fill=1): super(matrix,self).__init__([fill]*(n*(m or n))); self.n=n; self.m=m or n;
	def __repr__(self): return '\n'.join([' '.join(map(str,self[i*self.m:(i+1)*self.m])) for i in range(self.n)])
	def __getitem__(self,i): return list.__getitem__(self,i[0]*self.m+i[1])
	def __setitem__(self,i,a): list.__setitem__(self,i[0]*self.m+i[1],a)
		

m=matrix(5)
m[2,2]=3
print m
