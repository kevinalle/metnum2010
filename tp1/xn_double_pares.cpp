#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char*argv[]){
	if(argc==4){
		double x0=atof(argv[1]);
		double x1=atof(argv[2]);
		int r = atoi(argv[3]);
		/* Muller por sucesion */
		double x2;
		for(int i=0;i<r;i++){
			x2 = 108.-(815.-(1500./x0))/x1;
			x0 = x1;
			x1 = x2;
			cout << "{"<<x0<<","<<x1<<"},";
		}
		cout << endl;
	}
	return 0;
}
