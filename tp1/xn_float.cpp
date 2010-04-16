#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char*argv[]){
	if(argc==4){
		float x0=atof(argv[1]);
		float x1=atof(argv[2]);
		int r = atoi(argv[3]);
		/* Muller por sucesion */
		float temp;
		for(int i=0;i<r;i++){
			temp = 108.-(815.-(1500./x0))/x1;
			x0 = x1;
			x1 = temp;
			cout << x1 << endl;
		}
	}
	return 0;
}
