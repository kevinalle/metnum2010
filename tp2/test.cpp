#include <iostream>
using namespace std;

#include "Matriz.h"

#define forn(i,n) for(int i=0;i<n;i++)

int main(){
	Matriz A(3,3,.5);
	A(0,0)=1; A(0,1)=2; A(0,2)=3;
	A(1,0)=4; A(1,1)=5; A(1,2)=6;
	A(2,0)=7; A(2,1)=8; A(2,2)=9;
	cout << A << endl;
	A.factorizar();
//	A.factorizar();

//	A.printPLU();
//	cout << "L = " << A.getL() << endl;
//	cout << "U = " << A.getU() << endl;
cout << 0 << endl;
	Matriz b(3,1,0.1);
	b.def(1,0,0.2); b.def(2,0,0.3);
cout << 1 << endl;
	//Vector v(3,0.1);
//	v.def(1,0,0.2); v.def(2,0,0.3);
cout << 2 << endl;
//	cout << v << endl;
cout << 3 << endl;
	Matriz R = A.resolver(b);
	cout << "res: " << R << endl;
	cout << "res: " << A*R << " = " << b << " ?" <<endl;
cout << 4 << endl;
	return 0;
}
