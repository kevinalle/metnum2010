#include <math.h>
#include <iostream>
using namespace std;

double abs( double n ){
	return max(n,-n);
}

double Muller(const double& x0 /* x[n-1] */, const double& x1 /* x[n-2] */){
	return 108.-(815.-(1500./x0))/x1;
}

int main(){
	double x0, x1, e;
	e = 1e-3;
	while( cin >> x0 >> x1 && ( x0!=0 || x1!=0 ) ){

		/* Muller por sucesion */
		double x2;
		int r = 1;
		do{
			x2 = 108.-(815.-(1500./x0))/x1;
			x0 = x1;
			x1 = x2;
			r++;
			cout << "   "<< x1 << endl;
		}while( abs(x1-x0) >= e );

		cout << x1 << endl;//" " << r << endl;
	}
	return 0;
}
