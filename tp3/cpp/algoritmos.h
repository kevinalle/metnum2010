#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <list>
#include <iostream>
#include <math.h>
#include <stdlib.h>	// abs()
using namespace std;

#include "Matriz.h"

#define forn(i,n) for(int i=0;i<n;i++)
#define forsn(i,s,n) for(int i=s;i<n;i++)
#define forrn(i,n) for(int i=(n)-1;i>=0;i--)
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)

struct Punto
{
	Punto() {}
	Punto(double _x, double _y) : x(_x), y(_y) {}
	double x;
	double y;
};

struct Spline
{
	double a;
	double b;
	double c;
	double d;
};

ostream& operator << (ostream& os, const Spline& S)
{
	//os <<'{'<<S.a<<','<<S.b<<','<<S.c<<','<<S.d<<'}';
	os <<S.a<<' '<<S.b<<' '<<S.c<<' '<<S.d;
	return os;
}

Punto* ToArray(list<Punto> lista)
{
	Punto* res = new Punto[lista.size()];
	int i=0;
	forall(it,lista)
	{
		res[i] = *it;
		i++;
	}
	return res;
}

double* ToArray(list<double> lista)
{
	double* res = new double[lista.size()];
	int i=0;
	forall(it,lista)
	{
		res[i] = *it;
		i++;
	}
	return res;
}

Spline* GenerarSpline(const Punto* datos, const int n)
{
	double a[n]; forn(i,n) a[i] = datos[i].y;
	double h[n-1];
	forn(i,n-1) h[i] = datos[i+1].x - datos[i].x;
	double alpha[n]; alpha[0]=0; forsn(i,1,n) alpha[i] = (3./h[i])*(a[i+1]-a[i])-(3./h[i-1])*(a[i]-a[i-1]);
	double l[n]; double mu[n]; double z[n]; l[0] = mu[0] = z[0] = 0;
	forsn(i,1,n)
	{
		l[i] = 2.*(datos[i+1].x-datos[i-1].x)-h[i-1]*mu[i-1];
		mu[i] = h[i]/l[i];
		z[i] = (alpha[i]-h[i-1]*z[i-1])/l[i];
	}
	double c[n]; double b[n-1]; double d[n-1];
	l[n-1] = 1; z[n-1] = c[n-1] = 0;
	forrn(j,n-1)
	{
		c[j] = z[j]-mu[j]*c[j+1];
		b[j] = (a[j+1]-a[j])/h[j] - h[j]*(c[j+1]+2.*c[j])/3.;
		d[j] = (c[j+1]-c[j])/(3.*h[j]);
	}
	Spline* P = new Spline[n-1];
	forn(i,n-1)
	{
		P[i].a = a[i];
		P[i].b = b[i];
		P[i].c = c[i];
		P[i].d = d[i];
	}
	return P;
}

double P3(const Spline& S, double x)
{
	return S.d*x*x*x + S.c*x*x + S.b*x + S.a;
}

double PN(const Matriz& P, const double& x)
{
	int grado = P.Filas()-1;
	double res=0;
	forn(i,grado+1)
		res += P(i,0)*pow(x,grado-i);
	return res;
}

int ProximaRaizDiscreta(const Spline& S, int x_ini)
{
	int x = x_ini;
	double y0=P3(S,x); x++;
	double y1=P3(S,x); x++;
	while(y1>0)
	{
		x++;
		y0 = y1;
		y1 = P3(S,x);
		if(y1>y0)
			return -1;
	}
	return ( abs(y1)<y0 ? x : x-1 );
}

int ProximaRaizDiscreta(const Matriz& P, int x_ini)
{
	int x = x_ini;
	double y0=PN(P,x); x++;
	double y1=PN(P,x); x++;
	while(y1>0)
	{
		x++;
		y0 = y1;
		y1 = PN(P,x);
		if(y1>y0) return -1;
	}
	return ( abs(y1)<y0 ? x : x-1 );
}

Matriz T_CM(Matriz x, int grado)
{
	Matriz res(x.Filas(),grado);
	forn(i,res.Filas()) forn(j,res.Columnas())
	{
		res(i,j) = pow(x(i,0),res.Columnas()-j-1);
	}
	return res;
}

Matriz CM(const double* x, const double* y, const int n, const int grado)
{
	Matriz T(T_CM(Matriz(x,n,1),grado+1));
	Matriz T_t(T.T());
	Matriz A(T_t*T);
	Matriz b(T_t*Matriz(y,n,1));
	return A.resolver(b);
}

#endif

