#include "Matriz.h"
#include<vector>
using namespace std;
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)
#define forrn(i,n) for(int i=(n)-1;i>=0;i--)

Matriz& T_CM(Matriz x, int grado){
	Matriz* res = new Matriz(x.Filas(),grado+1);
	forn(i,res->Filas()) forn(j,res->Columnas()){
		(*res)(i,j) = pow(x(i,0),res->Columnas()-j-1);
	}
	return *res;
}

vector<double> CM(const vector<double>& x, const vector<double>& y, const int grado){
	int n = x.size();

	Matriz X(n,1);
	Matriz Y(n,1);

	// transformo de vector a matriz
	forn(i,n){
		X(i,0)=x[i];
		Y(i,0)=y[i];
	}
	Matriz T(T_CM(X,grado));
	Matriz T_t(T.T());
	Matriz A(T_t*T);
	Matriz b(T_t*Y);
	cout << b << endl;
	Matriz res(A.resolver(b));
	
	// transformo de matriz a vector
	vector<double> ret;
	forrn(i,grado+1) ret.push_back(res(i,0));
	
	return ret;
}
