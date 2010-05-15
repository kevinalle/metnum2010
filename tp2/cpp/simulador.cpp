#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include "Vector.h"
#include "Matriz.h"
#include <string>
using namespace std;
#define G 0.0001488180711083514625549864281980165853856665309337938391
#define F(i,j,x) (-G*Cuerpos[i].m*Cuerpos[j].m*(y[3*N+3*i+x]-y[3*N+3*j+x])/(dist*dist*dist))
#define yX(i) y[3*N+3*(i)]
#define yY(i) y[3*N+3*(i)+1]
#define yZ(i) y[3*N+3*(i)+2]
#define sq(x) ((x)*(x))

#define DEBUG 1

typedef Vector3 V3;
typedef Vector Vn;
struct Cuerpo{
	Cuerpo(string _name,double _m, V3 _x, V3 _v=V3()):name(_name),m(_m),x(_x),v(_v){}
	string name;
	double m;
	V3 x,v;
	friend ostream& operator<<(ostream&out,const Cuerpo& c){out<<c.name;return out;}
};
typedef Cuerpo Planeta;

int days;
int resolution;
int outresolution;
double dt;

//Cuerpo sistema[]={sol, mercurio, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton}; // Cuerpos a considerar en la simulacion
int N;//=sizeof(sistema)/sizeof(Cuerpo);
vector<Cuerpo> Cuerpos;//(sistema, sistema+N);

void printPos(const Vn& y){
	forn(i,N) cout << "(" << y[3*N+3*i] << "," << y[3*N+3*i+1] << "," << y[3*N+3*i+2] << ")" <<" ";
	cout<<endl;
}

Vn f(const Vn& y){
	Vn res(6*N,0);
	forn(i,N){
		double sumx=0,sumy=0,sumz=0;
		forn(j,N) if(j!=i){
			double dist=(V3(y[3*N+3*i],y[3*N+3*i+1],y[3*N+3*i+2])-V3(y[3*N+3*j],y[3*N+3*j+1],y[3*N+3*j+2])).norm();
			sumx+=F(i,j,0);
			sumy+=F(i,j,1);
			sumz+=F(i,j,2);
		}
		res[3*i]  =sumx/Cuerpos[i].m;
		res[3*i+1]=sumy/Cuerpos[i].m;
		res[3*i+2]=sumz/Cuerpos[i].m;
	}
	forn(i,3*N) res[i+3*N]=y[i];
	return res;
}

Matriz dFdx(int i, int j, const Vn& y){
	double d=sqrt( sq(yX(i)-yX(j)) + sq(yY(i)-yY(j)) + sq(yZ(i)-yZ(j)) );
	double d3=1/(d*d*d);
	double d5=3/(d*d*d*d*d);
	double dx=yX(i)-yX(j);
	double dy=yY(i)-yY(j);
	double dz=yZ(i)-yZ(j);
	Matriz dFdx(3,3,0);
	dFdx(0,0)=d3-d5*dx*dx; dFdx(0,1) = -d5*dx*dy; dFdx(0,2) = -d5*dx*dz;
	dFdx(1,0) = -d5*dx*dy; dFdx(1,1)=d3-d5*dy*dy; dFdx(1,2) = -d5*dy*dz;
	dFdx(2,0) = -d5*dx*dz; dFdx(2,1) = -d5*dy*dz; dFdx(2,2)=d3-d5*dz*dz;
	return -G*Cuerpos[i].m*Cuerpos[j].m*dFdx;
}

Matriz Df(const Vn& y){
	Matriz res(6*N,6*N,0);

	// lleno A21
	forn(i,3*N) forn(j,3*N) if(i==j) res(3*N+i,j) = 1;

	// lleno A12
	forn(i,N) forn(j,N) {
		Matriz S(3,3,0);
		if(i==j){
			forn(k,N) if(k!=i) S += dFdx(i,k,y);
			S *= (1/Cuerpos[i].m);
		}else{
			S = (1/Cuerpos[i].m)*dFdx(i,j,y);
		}
		forn(ii,3) forn(jj,3) res(3*i+ii,3*N+3*j+jj) = (double)S(ii,jj);
	}

	return res;
}

Matriz Taylor(const Vn& y){
	Matriz Dfy = Df(y);
	Matriz A( Matriz::ID(6*N) - dt*Dfy );
	return A.resolver( y + dt*( f(y) - Dfy*y ) );
}

int main(int argc, char*argv[]){

	//PARSE OPT
	if(argc>1) days=atoi(argv[1]); else days=365;
	if(argc>2) resolution=atoi(argv[2]); else resolution=10000;
	if(argc>3) outresolution=atoi(argv[3]); else outresolution=100;
	dt=days/(float)resolution;
	
	//GET INPUT
	string name;
	double mass;
	V3 x,v;
	while( cin >> name >> mass >> x.X() >> x.Y() >> x.Z() >> v.X() >> v.Y() >> v.Z() ){
		Cuerpos.push_back(Cuerpo(name, mass, x, v));
		cout << name << " ";
	}
	cout << endl;
	N=Cuerpos.size();
	
	Vn y(6*N,0);

	forn(i,N){
		y[3*i]  	 = Cuerpos[i].v.X();
		y[3*i+1]	 = Cuerpos[i].v.Y();
		y[3*i+2]	 = Cuerpos[i].v.Z();
		y[3*i+3*N]   = Cuerpos[i].x.X();
		y[3*i+1+3*N] = Cuerpos[i].x.Y();
		y[3*i+2+3*N] = Cuerpos[i].x.Z();
	}

	// y=[v1,v2,...,vn,x1,x2,...,xn]

	printPos(y);
	forn(iter,resolution){
		y = Taylor(y);
		if(iter%(resolution/(outresolution-2))==0) printPos(y);
	}
	printPos(y);
	return 0;
}
