#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <assert.h>
using namespace std;

#define forn(i,n) for(int i=0;i<n;i++)
#define fornr(i,n) for(int i=n-1;0<=i;i--)
#define forsn(i,s,n) for(int i=s;i<n;i++)
#define forsnr(i,s,n) for(int i=n-1;s<=i;i--)

class Vector;

double abs(const double& n){
	return ( n<0 ? -n : n );
}

void print(ostream& os, const double* M, int n, int m){
	os << "size: " << n << "x" << m << endl;
	os << '[';
	forn(i,n){
		if(i!=0) os << ';';
		os << '[';
		forn(j,m){
			if(j!=0) os << ',';
			os << M[m*i + j];
		}
		os << ']' << endl;
	}
	os << ']' << endl;
}

void print(const int* M, int n, int m){
	cout << '[';
	forn(i,n){
		if(i!=0) cout << ';';
		cout << '[';
		forn(j,m){
			if(j!=0) cout << ',';
			cout << M[m*i + j];
		}
		cout << ']';
	}
	cout << ']';
}

class Matriz{

	public:

		/* Constructor. Toma filas - columnas - valor inicial de los campos */
		Matriz(const int _n, const int _m, const double& e = 0);

		/* Constructor por copia */
		Matriz(const Matriz& B);

		/* Constructor por copia de un array */
		Matriz(const double* B, const int _n, const int _m);

		/* Destructor */
		~Matriz();

		/* Devuelve la matriz traspuesta */
		Matriz T() const;

		int Filas() const;
		int Columnas() const;

		/* factoriza la matriz en PLU */
//		void factorizar();

		/* resuelve un sistema de ecuaciones con solucion b */
		/* requiere factorizacion previa */
		Matriz resolver(const Vector& b);

		/* resuelve un sistema de ecuaciones con solucion b */
		/* requiere factorizacion previa */
//		Matriz resolverPLU(const Matriz& b);

//		Matriz getL() const;
//		Matriz getU() const;
//		void printPLU() const;

		static Matriz ID(const int n);

		/* Operadores varios */

		double& operator () (const int i, const int j);
		const double& operator () (const int i, const int j) const;
		Matriz operator + (const Matriz& B) const;
		Matriz operator - (const Matriz& B) const;
		Matriz operator * (const Matriz& B) const;
		Matriz& operator += (const Matriz& B);
		Matriz& operator *= (const Matriz& B);
		Matriz& operator *= (const double& lambda);
		Matriz& operator = (const Matriz& A);
		friend Matriz operator * (const double& lambda, const Matriz& A);
		friend ostream& operator << (ostream& os, const Matriz& A);

	protected:

		int n, m;

		double* M;

		void triangular(Vector& res, double* U2, int* P2, const int k);
//		void triangularPLU(const int k);
//		void def(const int i, const int j, const double& e);
//		double& elem(const int i, const int j) const;
//		void desfactorizar();

};

class Vector: public Matriz{
	public:
		Vector(const int _n, const double& e) : Matriz(_n,1,e) {}
		Vector(const Matriz& V) : Matriz(V) {}
		Vector operator+(const Vector& B) const{return (Vector)((Matriz)(*this)+B);}
		double& operator[](const int i){ return M[i]; }
		const double& operator[](const int i) const { return M[i]; }
		friend ostream& operator<<(ostream& os, const Vector& V);
};

Matriz::Matriz(const int _n, const int _m, const double& e){
	n = _n; m = _m;
	M = new double[n*m];
	forn(i,n*m) M[i] = e;
}

Matriz::Matriz(const Matriz& B){
	n = B.n; m = B.m;
	M = new double[n*m]; forn(i,n) forn(j,m) (*this)(i,j) = B(i,j);//def(i,j,B.elem(i,j));
}

Matriz::Matriz(const double* B, const int _n, const int _m){
	n = _n; m = _m;
	M = new double[n*m]; forn(i,n*m) M[i] = B[i];
}

Matriz::~Matriz(){
	delete[] M;
}

Matriz Matriz::T() const {
	Matriz res(m,n);
	forn(i,m) forn(j,n) res(i,j) = (*this)(j,i);
	return res;
}

int Matriz::Filas() const
{
	return n;
}

int Matriz::Columnas() const
{
	return m;
}

/*
void Matriz::factorizar(){
	#if DEBUG==1
		assert(n==m);
	#endif
	if(L!=NULL) desfactorizar();

	L = new double[n*m];
	U = new double[n*m];
	P = new int[n];

	forn(i,n*m) L[i] = 0;
	forn(i,n*m) U[i] = M[i];
	forn(i,n) P[i] = i;

	forn(k,n-1) triangularPLU(k);

	forn(i,n) L[i*m + i] = 1;

}
*/

Matriz Matriz::resolver(const Vector& b){
	#if DEBUG==1
		assert( b.n==n && b.m==1 );
	#endif

	double U2[n*m]; forn(i,n*m) U2[i] = M[i];
	int P2[n]; forn(i,n) P2[i] = i;

	//double res[n]; forn(i,n) res[i] = b.elem(i,0);
	Vector res(b);

	forn(k,n-1) triangular(res,U2,P2,k);

	fornr(i,n){
		forsn(j,i+1,n) res[i] -= U2[i*m + j]*res[j];
		#if DEBUG==1
			assert(U2[i*m + i]);
		#endif
		res[i] /= U2[i*m + i];
	}

	return res;
}

void Matriz::triangular(Vector& res, double* U2, int* P2, const int k){

	int f = k;
	double p = U2[f*m + k];

	// elijo la fila pivote donde el k-esimo elem es maximo
	forsn(i,k,n) if( abs(U2[i*m + k]) > abs(p) ){ f = i; p = U2[f*m + k]; }

	#if DEBUG==1
		if(p==0){
			clog << "SINGULAR!" << endl;
			assert(p!=0);
		}
	#endif

	// swapeo las filas f y k en U y res
	forn(j,n){
		double temp_U2 = U2[f*m + j];
		U2[f*m + j] = U2[k*m + j];
		U2[k*m + j] = temp_U2;
		double temp_r = res[f];
		res[f] = res[k];
		res[k] = temp_r;
	}

	// actualizo el vector de perumtación
	int temp = P2[f];
	P2[f] = P2[k];
	P2[k] = temp;

	// triangulo las filas k+1 -> n
	forsn(i,k+1,n){

		// elijo el m_ij
		double a = U2[i*m+k]/p;

		// la k-esima columna es 0
		U2[i*m+k] = 0;

		// calculo el valor de las columnas k+1 -> n
		forsn(j,k+1,n) U2[i*m+j] -= a*U2[k*m+j];

		res[i] -= a*res[k];
	}
}

/*
Matriz Matriz::resolverPLU(const Matriz& b){
	#if DEBUG==1
		assert( b.n==n && b.m==1 );
	#endif
	
	if(L==NULL) factorizar();

	double res[n];

	forn(i,n) res[i] = b(P[i],0);

	forn(j,n-1) forsn(i,j+1,n) res[i] -= L[i*m + j]*res[j];

	fornr(i,n){
		forsn(j,i+1,n) res[i] -= U[i*m + j]*res[j];
		#if DEBUG==1
			assert(U[i*m + i]);
		#endif
		res[i] /= U[i*m + i];
	}

	return Matriz(res,n,1);;
}

void Matriz::triangularPLU(const int k){

	int f = k;
	double p = U[f*m + k];

	// elijo la fila pivote donde el k-esimo elem es maximo
	forsn(i,k,n) if( abs(U[i*m + k]) > abs(p) ){ f = i; p = U[f*m + k]; }

	if(p==0){
		clog << "SINGULAR!" << endl;
		clog << "M: "; print(clog,M,n,m);
		clog << "U: "; print(clog,U,n,m);
	}

	// swapeo las filas f y k en L y U
	forn(j,n){

		double temp_U = U[f*m + j];
		U[f*m + j] = U[k*m + j];
		U[k*m + j] = temp_U;

		double temp_L = L[f*m + j];
		L[f*m + j] = L[k*m + j];
		L[k*m + j] = temp_L;

	}

	// actualizo el vector de perumtación
	int temp = P[f];
	P[f] = P[k];
	P[k] = temp;

	// triangulo las filas k+1 -> n
	forsn(i,k+1,n){

		// elijo el m_ij
		double a = U[ i*m + k ]/p;

		L[ i*m + k ] = a;

		// la k-esima columna es 0
		U[ i*m + k ] = 0;

		// calculo el valor de las columnas k+1 -> n
		forsn(j,k+1,n)

			U[ i*m + j ] -= a*U[ k*m + j ];

	}
}

Matriz Matriz::getL() const{
	return Matriz(L,n,m);
}

Matriz Matriz::getU() const{
	return Matriz(U,n,m);
}

void Matriz::printPLU() const{
	cout << "P = "; print(P,1,n); cout << endl;
	cout << "L = "; print(cout,L,n,m); cout << endl;
	cout << "U = "; print(cout,U,n,m); cout << endl;
}
*/

Matriz Matriz::ID(const int n){
	Matriz res(n,n,0);
	forn(i,n) res(i,i) = 1;
	return res;
}

double& Matriz::operator () (const int i, const int j){
	#if DEBUG==1
		assert(0<=i); assert(i<n);
		assert(0<=j); assert(j<m );
	#endif
	return M[m*i + j];
}

const double& Matriz::operator () (const int i, const int j) const {
	#if DEBUG==1
		assert(0<=i); assert(i<n);
		assert(0<=j); assert(j<m );
	#endif
	return M[m*i + j];
}

Matriz Matriz::operator * (const Matriz& B) const {
	#if DEBUG==1
		assert( m==B.n );
	#endif
	Matriz res(n,B.m,0);
	forn(i,res.n) forn(j,res.m) forn(k,m) res.M[i*res.m + j] += (*this)(i,k)*B(k,j);
	return res;
}

Matriz Matriz::operator + (const Matriz& B) const {
	#if DEBUG==1
		assert( n==B.n && m==B.m );
	#endif
	Matriz res(n,m);
	forn(i,n) forn(j,m) res(i,j) = (*this)(i,j)+B(i,j);
	return res;
}

Matriz Matriz::operator - (const Matriz& B) const {
	#if DEBUG==1
		assert( n==B.n && m==B.m );
	#endif
	Matriz res(n,m);
	forn(i,n) forn(j,m) res(i,j) = (*this)(i,j)-B(i,j);
	return res;
}

Matriz& Matriz::operator += (const Matriz& B){
	#if DEBUG==1
		assert( n==B.n && m==B.m );
	#endif
	forn(i,n) forn(j,m) (*this)(i,j)+=B(i,j);
	return (*this);
}

Matriz& Matriz::operator *= (const Matriz& B){
	#if DEBUG==1
		assert( n==B.n && m==B.m );
	#endif
	double* M2 = new double[n*m]; forn(i,n*m) M2[i] = 0;
	forn(i,n) forn(j,m) forn(k,m) M2[i*m + j] += (*this)(i,j)*B(i,j);
	delete M;
	M = M2;
	return (*this);
}

Matriz& Matriz::operator *= (const double& lambda){
	forn(i,n) forn(j,m) (*this)(i,j) *= lambda;
	return (*this);
}

Matriz& Matriz::operator = (const Matriz& A){
	#if DEBUG==1
		assert( n==B.n && m==B.m );
	#endif
	if( this!=&A )
		forn(i,n*m) M[i] = A.M[i];
	return *this;
}

Matriz operator * (const double& lambda, const Matriz& A){
	Matriz res(A);
	forn(i,A.n) forn(j,A.m) res(i,j) *= lambda;
	return res;
}

ostream& operator << (ostream& os, const Matriz& A){
	os << '[';
	forn(i,A.n){
		if(i!=0) os << ';';
		os << '[';
		forn(j,A.m){
			if(j!=0) os << ',';
			os << A.M[A.m*i + j];
		}
		os << ']' << endl;
	}
	os << ']';
	return os;
}

ostream& operator<<(ostream& os, const Vector& V){
	os << '[';
	forn(i,V.n){
		if(i!=0) os << ',';
		os << V.M[i];
	}
	os << ']';
	return os;
}

#endif
