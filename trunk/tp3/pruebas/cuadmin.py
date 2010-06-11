def linsolve(A,b):
	"""resolucion de sistemas lineales con triangulacion gausseana con pivoteo simple"""
	n=len(A)
	for i in range(n):
		maxval,maxj=-1,0
		#busco fila de mayor valor abs
		for j in range(i,n):
			if abs(A[j][i])>maxval: maxval=abs(A[j][i]);maxj=j
		#pivoteo
		A[maxj],A[i]=A[i],A[maxj]
		b[i],b[maxj]=b[maxj],b[i]
		#pongo 0s
		for j in range(i+1,n):
			m=float(A[j][i])/A[i][i]
			A[j][i]=0
			for k in range(i+1,n):
				A[j][k]-=m*A[i][k]
			b[j]-=m*b[i]
	
	#resuelvo
	x=[0]*n
	x[-1]=b[-1]/A[-1][-1]
	for i in reversed(range(n)):
		x[i]=(b[i]-sum(x[k]*A[i][k] for k in range(i+1,n)))/A[i][i]
	return x

def transposed(A):
	n=len(A)
	m=len(A[0])
	return [[A[i][j] for i in range(n)] for j in range(m)]

def mmmul(A,B):
	"""multiplicacion de matrices"""
	n=len(A)
	m=len(B)
	res=[[0]*n for _ in range(n)]
	for i in range(n):
		for j in range(n):
			for k in range(m):
				res[i][j]+=A[i][k]*B[k][j]
	return res

def mvmul(A,x):
	"""multiplicacion de matriz por vector"""
	n=len(A)
	m=len(x)
	return [sum(A[i][j]*x[j] for j in range(m)) for i in range(n)]

def cuadmin(x,y):
	"""devuelve coeficiontes (a0··an) para cuadrados minimos"""
	M=[[xx**j for j in reversed(range(5))] for xx in x]
	A=mmmul(transposed(M),M)
	b=mvmul(transposed(M),y)
	return [e for e in reversed(linsolve(A,b))]

#print cuadmin(*zip(*[(1,1),(2,2),(3,3),(4,4)]))
#print linsolve([[30,10],[10,4]],[30,10])
