#include <math.h>
#include <iostream>
using namespace std;

float abs( float n ){
	return max(n,-n);
}

float Muller(const float& x0 /* x[n-1] */, const float& x1 /* x[n-2] */){
	return 108. - (815.-(1500./x0))/x1;
}

int main(){
	float x0, x1, e;
	e = 0.00001;
	while( cin >> x0 >> x1 && ( x0!=0 || x1!=0 ) ){

		/* Muller por sucesion */
		float x2;
		int r = 1;
		do{
			x2 = Muller(x0,x1);
			x0 = x1;
			x1 = x2;
			r++;
		}while( abs(x1-x0) >= e );

		cout << x1 << endl;
	}
	return 0;
}
