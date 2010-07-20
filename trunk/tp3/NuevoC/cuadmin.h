#include "Matriz.h"
#include<vector>
using namespace std;
#define forall(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)

Matriz& T_CM(Matriz x, int grado){
	Matriz* res = new Matriz(x.Filas(),grado+1);
	forn(i,res->Filas()) forn(j,res->Columnas()){
		(*res)(i,j) = pow(x(i,0),res->Columnas()-j-1);
	}
	return *res;
}

vector<double>& CM(vector<double> x, vector<double> y, const int grado){

	clog << "============================================================" << endl;
	clog << "		CM INPUT" << endl;
	clog << "		x: "; forall(it,x) clog<<*it<<","; clog<<endl;
	clog << "		y: "; forall(it,y) clog<<*it<<","; clog<<endl;
	clog << "		grado: " << grado << endl << endl;
	
	int n = x.size();

	Matriz X(n,1);
	Matriz Y(n,1);

	// transformo de vector a matriz
	forn(i,n){
		X(i,0)=x[i];
		Y(i,0)=y[i];
	}

	clog << "		X: " << X << endl;
	clog << "		Y: " << Y << endl << endl;

	Matriz T(T_CM(X,grado));
	Matriz T_t(T.T());
	Matriz A(T_t*T);
cout << "		T: " << T << endl;
cout << "		T.t: " << T_t << endl << endl;
	Matriz b(T_t*Y);
cout << "		A: " << A << endl;
cout << "		b: " << b << endl;
	Matriz res(A.resolver(b));
cout << "		res: " << res << endl;
//	forn(i,n) clog<<res(i,0)<<","; clog<<endl;

	// transformo de matriz a vector

	vector<double>* ret = new vector<double>();
	forn(i,grado+1) ret->push_back(res(i,0));

	clog << endl << "		CM OUTPUT" << endl;
	clog << "		"; forall(it,*ret) clog<<*it<<","; clog<<endl;
	clog << "============================================================" << endl;

	return *ret;
}
