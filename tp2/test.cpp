#include <iostream>
using namespace std;

#include "Matriz.h"

#define forn(i,n) for(int i=0;i<n;i++)

int main(){
	Matriz A(3,3,.5);
	A.def(0,0,1); A.def(0,1,2); A.def(0,2,3);
	A.def(1,0,3); A.def(1,1,5); A.def(1,2,1);
	A.def(2,0,7); A.def(2,1,8); A.def(2,2,9);
	cout << A << endl;
	A.factorizar();

	A.printPLU();
//	Matriz b(3,1,0.1);

	// resolver anda ???

//	cout << "L = " << A.getL() << endl; ?? error de memoria
//	cout << "U = " << A.getU() << endl; ?? error de memoria
	return 0;
}
