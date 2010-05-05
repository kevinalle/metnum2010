#include <iostream>
using namespace std;

#include "Matriz.h"

#define forn(i,n) for(int i=0;i<n;i++)

int main(){
	Matriz A(3,3,.5);
	Matriz B(A);
	Matriz I(3,3); forn(i,3) I.def(i,i,1);
	Matriz V(3,1,2);
	A.def(1,1,.3);
	Matriz W = V.T();
	cout << A << endl;
	cout << B << endl;
	cout << (A*=I) << endl;
	return 0;
}
