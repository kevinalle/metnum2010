#include <iostream>
#include <list>
#include <vector>
#include "Vector.h"
#include "Matriz.h"
using namespace std;
#define G 0.0001488180711083514625549864281980165853856665309337938391
#define F(i,j,x) (-G*Cuerpos[i].m*Cuerpos[j].m*(y[3*N+3*i+x]-y[3*N+3*j+x])/(dist*dist*dist))
#define yX(i) y[3*N+3*i]
#define yY(i) y[3*N+3*i+1]
#define yZ(i) y[3*N+3*i+2]
#define sq(x) ((x)*(x))
#define ID(n) Matriz(n,n,0)

#define PRINTPOS(y) {forn(pos,N) cout<<"("<<y[3*N+3*pos]<<","<<y[3*N+3*pos+1]<<","<<y[3*N+3*pos+2]<<")"<<" "; cout<<endl;}

typedef Vector V;
typedef VectorN Vn;
struct Cuerpo{
	Cuerpo(double _m, V _x, V _v=V()):m(_m),x(_x),v(_v){}
	double m;
	V x,v;
};
typedef Cuerpo Planeta;

int days=365;
int resolution=800;
int outresolution=10;
double dt=days/(float)resolution;

//Cuerpo sol(1, V(0,0,0), V(0,0,0));
//Planeta mercurio(1, V(0,0,1), V(0,0,0));
Cuerpo sol(1.9891, V(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05), V(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08));
Planeta mercurio(0.0000003302, V(-2.563687782457914E-01, -3.810998677594219E-01, -8.153193298845162E-03), V(1.781451838572982E-02, -1.414097937982711E-02, -2.789632381177015E-03));
Planeta venus(0.0000048685, V(-2.745105890947935E-01, 6.675955871621595E-01, 2.473298509458710E-02), V(-1.880800003531344E-02, -7.736184882354628E-03, 9.795183384655537E-04));
Planeta tierra(0.0000059736, V(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05), V(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07));
Planeta luna (0.00000007349, V(-7.248557601516714E-01, -7.039097848869444E-01, 1.029051462977911E-04), V(1.220576787081027E-02, -1.211595432894550E-02, 4.775108508860639E-05));
Planeta marte(0.00000064185, V(-1.644799113455717E+00, 2.491823732968801E-01, 4.547552485947825E-02), V(-1.562104985945559E-03, -1.264976840237743E-02, -2.265804582138816E-04));
Planeta jupiter(0.00189813, V(4.814383212086098E+00, -1.241505788193773E+00, -1.026521185883739E-01), V(1.791829827597031E-03, 7.666882051378563E-03, -7.193518744890309E-05));
Planeta saturno(0.000568319, V(-9.498834472404264E+00, -4.314789953129710E-01, 3.854986365834464E-01), V(-4.474247412442582E-05, -5.585253179574848E-03, 9.894753356331143E-05));
Planeta urano(0.0000868103, V(2.006082145944713E+01, -1.065854769947036E+00, -2.638606790060225E-01), V(1.799636000766446E-04, 3.744193468414364E-03, 1.172307940858780E-05));
Planeta neptuno(0.00010241, V(2.502782007663963E+01, -1.656920556977117E+01, -2.355717002525958E-01), V(1.712539920668144E-03, 2.636211613138070E-03, -9.391170566983233E-05));
Planeta pluton(0.00000001314, V(2.019772677347968E+00, -3.163728071405687E+01, 2.801128087784796E+00), V(3.185164506154487E-03, -4.178107880823737E-04, -8.865662135620683E-04));
Cuerpo sistema[]={sol, mercurio};//, venus, tierra, marte, jupiter, saturno, urano, neptuno, pluton}; // Cuerpos a considerar en la simulacion
int N=sizeof(sistema)/sizeof(Cuerpo);
vector<Cuerpo> Cuerpos(sistema, sistema+N);

Vn f(const Vn& y){
	Vn res(6*N,0);
	forn(i,N){
		double sumx=0,sumy=0,sumz=0;
		forn(j,N) if(j!=i){
			double dist=(V(y[3*N+3*i],y[3*N+3*i+1],y[3*N+3*i+2])-V(y[3*N+3*j],y[3*N+3*j+1],y[3*N+3*j+2])).norm();
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

Matriz dFdx(int i, int j, Vn& y){
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

	Matriz A12(3*N,3*N);
	Matriz A21(3*N,3*N);

	forn(i,N) forn(j,N) {
		
	}
	return res;
}

Matriz Taylor(const Vn& y){
	Matriz Dfy = Df(y);
	Matriz A( ID(6*N) - dt*Dfy );
	Vn b = y + dt*( f(y) - Dfy*y );
	return A.resolver(b);
}

int main(int argc, char*argv[]){
	Vn y(6*N,0);
	forn(i,N){
		y[3*i]  =Cuerpos[i].v.X();
		y[3*i+1]=Cuerpos[i].v.Y();
		y[3*i+2]=Cuerpos[i].v.Z();
		y[3*i+3*N]  =Cuerpos[i].x.X();
		y[3*i+1+3*N]=Cuerpos[i].x.Y();
		y[3*i+2+3*N]=Cuerpos[i].x.Z();
	}
	// y=[v1,v2,...,vn,x1,x2,...,xn]
	
	PRINTPOS(y);
	forn(iter,resolution){
		y=y+dt*f(y);		
		if(iter%(resolution/(outresolution-2))==0) PRINTPOS(y);//cout << y << endl;
	}
	PRINTPOS(y);
	return 0;
}
