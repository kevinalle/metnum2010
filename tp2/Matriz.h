#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <assert.h>
using namespace std;

#define forn(i,n) for(int i=0;i<n;i++)

class Matriz{

	public:

		/* Constructor. Toma filas - columnas - valor inicial de los campos */
		Matriz(const int _n, const int _m, const double& e = 0);

		/* Constructor por copia */
		Matriz(const Matriz& B);

		/* Destructor */
		~Matriz();

		/* define al elemento (i,j) como e */
		void def(const int i, const int j, const double& e);

		/* devuelve el valor del elemento (i,j) */
		double elem(const int i, const int j) const;

		/* Devuelve la matriz traspuesta */
		Matriz T() const;

		/* Operadores varios */

		Matriz operator + (const Matriz& B) const;
		Matriz operator * (const Matriz& B) const;
		Matriz& operator += (const Matriz& B);
		Matriz& operator *= (const Matriz& B);
		Matriz& operator *= (const double& lambda);
		friend Matriz operator * (const double& lambda, const Matriz& A);
		friend ostream& operator << (ostream& os, const Matriz& A);

	private:

		int n, m;

		double* M;

};

Matriz::Matriz(const int _n, const int _m, const double& e){
	n = _n; m = _m;
	M = new double[n*m];
	forn(i,n*m) M[i] = e;
}

Matriz::Matriz(const Matriz& B){
	n = B.n; m = B.m;
	M = new double[n*m];
	forn(i,n) forn(j,m) def(i,j,B.elem(i,j));
}

Matriz::~Matriz(){
	delete M;
}

void Matriz::def(const int i, const int j, const double& e){
	assert( 0<=i && i<n && 0<=j && j<m );
	M[m*i + j] = e;
}

double Matriz::elem(const int i, const int j) const {
	assert( 0<=i && i<n && 0<=j && j<m );
	return M[m*i + j];
}

Matriz Matriz::T() const {
	Matriz res(m,n);
	forn(i,m) forn(j,n) res.def(i,j, elem(j,i));
	return res;
}

Matriz Matriz::operator * (const Matriz& B) const {
	assert( m==B.n );
	Matriz res(n,B.m,0);
	forn(i,res.n) forn(j,res.m) forn(k,m) res.M[i*res.m + j] += elem(i,k)*B.elem(k,j);
	return res;
}

Matriz Matriz::operator + (const Matriz& B) const {
	assert( n==B.n && m==B.m );
	Matriz res(n,m);
	forn(i,n) forn(j,m) res.def(i,j, elem(i,j)+B.elem(i,j));
	return res;
}

Matriz& Matriz::operator += (const Matriz& B){
	assert( n==B.n && m==B.m );
	forn(i,n) forn(j,m) def(i,j, elem(i,j)+B.elem(i,j));
	return (*this);
}

Matriz& Matriz::operator *= (const Matriz& B){
	assert( n==B.n && m==B.m );
	double* M2 = new double[n*m]; forn(i,n*m) M2[i] = 0;
	forn(i,n) forn(j,m) forn(k,m) M2[i*m + j] += elem(i,k)*B.elem(k,j);
	delete M;
	M = M2;
	return (*this);
}

Matriz& Matriz::operator *= (const double& lambda){
	forn(i,n) forn(j,m) def(i,j,lambda*elem(i,j));
	return (*this);
}

Matriz operator * (const double& lambda, const Matriz& A){
	Matriz res(A);
	forn(i,A.n) forn(j,A.m) res.def(i,j,lambda*res.elem(i,j));
	return res;
}

ostream& operator << (ostream& os, const Matriz& A){
	os << '[';
	forn(i,A.n){
		if(i!=0) os << ',';
		os << '[';
		forn(j,A.m){
			if(j!=0) os << ',';
			os << A.M[A.m*i + j];
		}
		os << ']';
	}
	os << ']';
	return os;
}

#endif
