#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <assert.h>
using namespace std;

#define forn(i,n) for(int i=0;i<n;i++)
#define fornr(i,n) for(int i=n-1;0<=i;i--)
#define forsn(i,s,n) for(int i=s;i<n;i++)
#define forsnr(i,s,n) for(int i=n-1;s<=i;i--)

void print(const double* M, int n, int m){
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

		/* define al elemento (i,j) como e */
		void def(const int i, const int j, const double& e);

		/* devuelve el valor del elemento (i,j) */
		double& elem(const int i, const int j) const;

		/* Devuelve la matriz traspuesta */
		Matriz T() const;

		/* factoriza la matriz en PLU */
		void factorizar();

		/* resuelve un sistema de ecuaciones con solucion b */
		/* requiere factorizacion previa */
		Matriz resolver(const Matriz& b) const;

		Matriz getL() const;
		Matriz getU() const;
		void printPLU() const;

		/* Operadores varios */

		Matriz operator + (const Matriz& B) const;
		Matriz operator * (const Matriz& B) const;
		Matriz& operator += (const Matriz& B);
		Matriz& operator *= (const Matriz& B);
		Matriz& operator *= (const double& lambda);
		friend Matriz operator * (const double& lambda, const Matriz& A);
		friend ostream& operator << (ostream& os, const Matriz& A);
		double& operator()(const int i, const int j){return elem(i,j);}

	protected:

		int n, m;

		double* M;
		double* L;
		double* U;
		int* P;

		void triangular(const int i);

};

class VectorN: public Matriz{
	public:
		VectorN(const int _n, const double& e):Matriz(_n,1,e){}
		VectorN(const Matriz& V):Matriz(V){}
		VectorN operator+(const VectorN& B) const{return VectorN(Matriz(*this)+B);}
		double& operator[](const int i){return elem(i,0);}
		friend ostream& operator<<(ostream& os, const VectorN& V){
			os << '[';
			forn(i,V.n){
				if(i!=0) os << ',';
				os << V.M[i];
			}
			os << ']';
			return os;
		}
};

Matriz::Matriz(const int _n, const int _m, const double& e){
	n = _n; m = _m;
	M = new double[n*m]; forn(i,n*m) M[i] = e;
	L = NULL; U = NULL; P = NULL;
}

Matriz::Matriz(const Matriz& B){
	n = B.n; m = B.m;
	M = new double[n*m]; forn(i,n) forn(j,m) def(i,j,B.elem(i,j));
	L = NULL; U = NULL; P = NULL;
}

Matriz::Matriz(const double* B, const int _n, const int _m){
	n = _n; m = _m;
	M = new double[n*m]; forn(i,n*m) M[i] = B[i];
	L = NULL; U = NULL; P = NULL;
}

Matriz::~Matriz(){
	delete[] M;
	delete[] L;
	delete[] U;
	delete[] P;
}

void Matriz::def(const int i, const int j, const double& e){
	assert( 0<=i && i<n && 0<=j && j<m );
	M[m*i + j] = e;
}

double& Matriz::elem(const int i, const int j) const {
	assert(0<=i); assert(i<n);
	assert(0<=j); assert(j<m );
	return M[m*i + j];
}

Matriz Matriz::T() const {
	Matriz res(m,n);
	forn(i,m) forn(j,n) res.def(i,j, elem(j,i));
	return res;
}

void Matriz::factorizar(){
	assert(n==m);

	delete[] L; L = new double[n*m];
	delete[] U; U = new double[n*m];
	delete[] P; P = new int[n];

	forn(i,n*m) L[i] = 0;
	forn(i,n*m) U[i] = M[i];
	forn(i,n) P[i] = i;

	forn(k,n-1) triangular(k);

	forn(i,n) L[i*m + i] = 1;

}

Matriz Matriz::resolver(const Matriz& b) const{
	assert( b.n==n && b.m==1 );

	double bb[n]; forn(i,n) bb[i] = b.elem(P[i],0);
	double res[n];

	fornr(i,n){

		res[i] = bb[i];

		forsn(j,i+1,n) res[i] -= res[j]*U[i*m + j];

		res[i] /= U[i*m + i];

	}

	Matriz Pres(n,1);
	forn(i,n) Pres.M[P[i]] = res[i];

	return Pres;
}

void Matriz::triangular(int k){

	int f = k;
	double p = U[f*m + k];

	// elijo la fila pivote
	forsn(i,k,n) if(U[i*m + k] > p){ f = i; p = U[f*m + k]; }

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

//cout << "	L: "; print(L,n,m); cout << endl;
//cout << "	U: "; print(U,n,m); cout << endl;
//cout << "	Permutacion: "; print(P,1,n); cout << endl;

}

Matriz Matriz::getL() const{
	return Matriz(L,n,m);
}

Matriz Matriz::getU() const{
	return Matriz(U,n,m);
}

void Matriz::printPLU() const{
	cout << "P = "; print(P,1,n); cout << endl;
	cout << "L = "; print(L,n,m); cout << endl;
	cout << "U = "; print(U,n,m); cout << endl;
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
		if(i!=0) os << ';';
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
