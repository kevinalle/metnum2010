def spline(data):
	n=len(data)-1
	x,y=zip(*data)
	a=y[:]
	h=[x[i+1]-x[i] for i in range(n)]
	alfa=[0]+[(3./h[i])*(a[i+1]-a[i])-(3./h[i-1])*(a[i]-a[i-1]) for i in range(1,n)]
	b,d=[0]*n,[0]*n
	c,l,mu,z=[0]*(n+1),[0]*(n+1),[0]*(n+1),[0]*(n+1)
	l[0],mu[0],z[0]=1,0,0
	for i in range(1,n):
		l[i]=2*(x[i+1]-x[i-1])-h[i-1]*mu[i-1]
		mu[i]=h[i]/l[i]
		z[i]=(alfa[i]-h[i-1]*z[i-1])/l[i]
	l[n],z[n],c[n]=1,0,0
	for j in reversed(range(n)):
		c[j]=z[j]-mu[j]*c[j+1]
		b[j]=(a[j+1]-a[j])/h[j]-h[j]*(c[j+1]+2*c[j])/3.
		d[j]=(c[j+1]-c[j])/(3*h[j])
	return zip(a,b,c,d,x)

if __name__=="__main__":
	print spline([(0,0),(1,1),(2,2)])
