#include <math.h>
#include <iostream>
using namespace std;

double abs( double n ){
	return max(n,-n);
}

int main(){
	double x0, x1;
	double e=.001;
	//while( cin >> x0 >> x1 && ( x0!=0 || x1!=0 ) ){
	for(double x0s=-8;x0s<13;x0s+=.25) for(double x1s=-5;x1s<16;x1s+=.25) if(x0!=0 && x1!=0){
		x0=x0s;
		x1=x1s;
		/* Muller por sucesion */
		double temp;
		int r = 1;
		do{
			temp = 108.-(815.-(1500./x0))/x1;
			x0 = x1;
			x1 = temp;
			r++;
		}while( abs(x1-100)>e && r<20  );

		cout << "{"<<x0s<<","<<x1s<<","<<r<<"}, ";
	}
	cout << endl;
	return 0;
}
