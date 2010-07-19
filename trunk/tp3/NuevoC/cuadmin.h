#include "Matriz.h"
using namespace std;

Matriz T_CM(Matriz x, int grado){
	Matriz res(x.Filas(),grado);
	forn(i,res.Filas()) forn(j,res.Columnas()){
		res(i,j) = pow(x(i,0),res.Columnas()-j-1);
	}
	return res;
}

Matriz CM(vector<double> x, vector<double> y, const int grado){
	int n=x.size();
	Matriz X(n,1);
	Matriz Y(n,1);
	forn(i,n){
		X(i,0)=x[i];
		Y(i,0)=y[i];
	}
	Matriz T(T_CM(X,grado+1));
	Matriz T_t(T.T());
	Matriz A(T_t*T);
	Matriz b(T_t*Y);
	return A.resolver(b);
}
