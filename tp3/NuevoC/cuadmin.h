#include "Matriz.h"
#include<vector>
using namespace std;
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)

Matriz T_CM(Matriz x, int grado){
	Matriz res(x.Filas(),grado);
	forn(i,res.Filas()) forn(j,res.Columnas()){
		res(i,j) = pow(x(i,0),res.Columnas()-j-1);
	}
	return res;
}

vector<double> CM(vector<double> x, vector<double> y, const int grado){
	//clog << "CM" << endl;
	int n=x.size();
	Matriz X(1,n+1);
	Matriz Y(1,n+1);
	forn(i,n){
		X(0,i)=x[i];
		Y(0,i)=y[i];
	}
	Matriz T(T_CM(X,grado+1));
	Matriz T_t(T.T());
	Matriz A(T_t*T);
	Matriz b(T_t*Y);
	Matriz res(A.resolver(b));
forn(i,n) clog<<res(i,0)<<","; clog<<endl;
	vector<double> ret;
	forn(i,grado) ret.push_back(res(0,i));
	//clog << "endCM" << endl;
forall(it,ret) clog<<*it<<".."; clog<<endl;
	return ret;
}
