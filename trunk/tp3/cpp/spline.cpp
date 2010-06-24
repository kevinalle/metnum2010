#include <iostream>
#include <math.h>
#include <stdlib.h>	// abs()
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define forsn(i,s,n) for(int i=s;i<n;i++)
#define forrn(i,n) for(int i=(n)-1;i>=0;i--)
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)

struct Punto{
	Punto() {}
	Punto(double _x, double _y) : x(_x), y(_y) {}
	double x;
	double y;
};

struct Spline{
	double a;
	double b;
	double c;
	double d;
};

Spline* GenerarSpline(const Punto* datos, const int n){
	double a[n]; forn(i,n) a[i] = datos[i].y;
	double h[n-1];
	forn(i,n-1) h[i] = datos[i+1].x - datos[i].x;
	double alpha[n]; alpha[0]=0; forsn(i,1,n) alpha[i] = (3./h[i])*(a[i+1]-a[i])-(3./h[i-1])*(a[i]-a[i-1]);
	double l[n]; double mu[n]; double z[n]; l[0] = mu[0] = z[0] = 0;
	forsn(i,1,n){
		l[i] = 2.*(datos[i+1].x-datos[i-1].x)-h[i-1]*mu[i-1];
		mu[i] = h[i]/l[i];
		z[i] = (alpha[i]-h[i-1]*z[i-1])/l[i];
	}
	double c[n]; double b[n-1]; double d[n-1];
	l[n-1] = 1; z[n-1] = c[n-1] = 0;
	forrn(j,n-1){
		c[j] = z[j]-mu[j]*c[j+1];
		b[j] = (a[j+1]-a[j])/h[j] - h[j]*(c[j+1]+2.*c[j])/3.;
		d[j] = (c[j+1]-c[j])/(3.*h[j]);
	}
	Spline* P = new Spline[n-1];
	forn(i,n-1){
		P[i].a = a[i];
		P[i].b = b[i];
		P[i].c = c[i];
		P[i].d = d[i];
	}
	return P;
}

int main(){
	Punto data []={Punto(0,0),Punto(1,1),Punto(2,2)};
	Spline* S=GenerarSpline(data, 3);
	forn(i,2) cout<<S[i].a<<" "<<S[i].b<<" "<<S[i].c<<" "<<S[i].d<<endl;
	return 0;
}
