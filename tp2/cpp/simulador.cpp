#include <iostream>
#include <cstdlib>
#include <list>
#include <string.h>
#include <vector>
#include "Vector.h"
#include "Matriz.h"
#include <string>
using namespace std;
// UNIDADES
// tiempo: 		dias
// distancia: 	AU
// masa: 		1e30 Kg
#define G 0.0001488180711083514625549864281980165853856665309337938391
#define F(i,j,x) (-G*Cuerpos[i].m*Cuerpos[j].m*(y[3*N+3*i+x]-y[3*N+3*j+x])/(dist*dist*dist))
#define yX(i) y[3*N+3*(i)]
#define yY(i) y[3*N+3*(i)+1]
#define yZ(i) y[3*N+3*(i)+2]
#define XYZ(i) V3(yX(i),yY(i),yZ(i))
#define sq(x) ((x)*(x))
#define NEXT(y) METODO1(y) // Elijo el metodo
#define METODO1(y) y+dt*f(y)
#define METODO2(y) Taylor(y)
#define METODO3(y) MetodoIterativo(y,1e-4);


/* 0=OFF 1=ON */
#define DEBUG 1

#define INF 2147483647

enum sim_t{ Simulacion, Misil };
enum misil_t{ Proyectil, BombaOscura };

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
typedef pair<bool,int> Option;

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
void printNames(){
	forn(i,N) cout << Cuerpos[i].name << " "; cout << endl;
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
			S *= (1./Cuerpos[i].m);
		}else{
			S = (1./Cuerpos[i].m)*dFdx(i,j,y);
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

// funcion de "distancia" entre dos resultados
double dist(const Vn& y){
	double res = 0;
	forn(i,6*N) res += sq(y[i]);
	return sqrt(res);
}

Vn MetodoIterativo(const Vn& y, const double dx){
	Vn w0(y);
	Vn w1(y);
	double d0 = INF;
	double d1 = INF;
//	int max_iter = 1000;
	int i=0;
	do{

		w0 = w1;
		Matriz Dfw = Df(w0);
		Matriz A( Matriz::ID(6*N) - dt*Dfw );
		Matriz B( y + dt*( f(w0) - Dfw*w0 ) );
		//forn(iii,6*N) forn(jjj,6*N){ assert(!isnan(A(iii,jjj)));  assert(!isnan(B(iii,jjj)));}
		w1 = A.resolver( B );

		d0 = d1;
		d1 = dist(w1-w0);
		i++;

		//if(d1<dx) return w1;

		//clog << Vn(w0-w1) << endl;
	}while( d1<d0 && d1<dx /*&& i<max_iter*/ );
	return w0;
}

Vn makeY(){
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
	return y;
}

pair<double,int> mindist(const Vn& y_in, int obj, int target){
	// Devuelve la distancia minima que alcanzan los objetos obj y target mientras se esten acercando y mientras no supere el tiempo de simulacion
	Vn y(y_in);
	double d=(XYZ(obj)-XYZ(target)).norm();
	double dans;
	int i=0;
	do{
		dans=d;
		y=NEXT(y);
		d=(XYZ(obj)-XYZ(target)).norm();
	}while(d<dans && ++i<resolution);
	return pair<double,int>(dans,i);
}

/* Muestra un menu de ayuda de opciones de linea de comandos
 * Es invocado con la opcion -h o al parsear una opcion extraña */
void help(){
	clog << "Modo de uso: ./simulador < inputfile [opciones]" << endl;
	clog << "opciones:" << endl;
	clog << "	-d | --days: es el tiempo de simulación en dias. default= 365." << endl;
	clog << "	-dt: es el intervalo de tiempo discreto de simulación en dias. default: .41 (1 hora)" << endl;
	clog << "	-or | --outresolution: es la cantidad de puntos que devuelve el programa distribuidos uniformemente en el el tiempo de simulación." << endl;
	clog << "	-h | --help: muestra este mensaje de ayuda." << endl;
}

/* Se encarga de parsear las opciones de linea de comandos
 * e inicializar las variables correspondientes */
void parse_options(int argc, char*argv[]){

	bool opt_days; opt_days=false;
	bool opt_dt; opt_dt=false;
	bool opt_outres; opt_outres=false;

	forsn(i,1,argc){
		if(strcmp( argv[i],"--days")==0 || strcmp(argv[i],"-d")==0 ){
			opt_days=true;
			days = atoi(argv[++i]);
		}else if(strcmp(argv[i],"-dt")==0){
			opt_dt=true;
			dt = atof(argv[++i]);
		}else if( strcmp(argv[i],"--outresolution")==0 || strcmp(argv[i],"-or")==0 ){
			opt_outres=true;
			outresolution = atoi(argv[++i]);
		}else if( strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-h")==0 ){
			help();
			exit(0);
		}else{
			clog << "invalid option: " << argv[i] << endl;
			help();
			exit(0);
		}
	}

	if(!opt_days) days=365;
	if(!opt_dt) dt=.041;
	if(!opt_outres) outresolution=atoi(argv[3]); else outresolution=100;

	resolution=days/dt;
}

/* Se encarga de leer de la entrada estandard los planetas a simular
 * junto con sus valores iniciales */
void init_planets(){
	string name; double mass; V3 x,v;
	while( cin >> name >> mass >> x.X() >> x.Y() >> x.Z() >> v.X() >> v.Y() >> v.Z() ){
		Cuerpos.push_back(Cuerpo(name, mass, x, v));
	}
}

/* Inicializa los datos necesarios del misil elegido */
void init_misil(const V3& target_pos, const misil_t type){

	double v_p_ini, m_p; string name;

	if(type==Proyectil){
		// Si quiero un Torpedo de protones
		v_p_ini=0.147852244; // 256 km/s = .14 AU/days
		m_p = 1e-30;
		name = "Proyectil";
	}else{
		// Si quiero una Bomba oscura
		v_p_ini=0.0346528697; // 60 km/s = .03 AU/days
		m_p = 5e-5;
		name = "Bomba oscura";
	}

	V3 x_p(-20., .005, 0.);
	V3 v_p( v_p_ini*(target_pos-x_p).normalize() );

	Cuerpos.push_back(Cuerpo(name, m_p, x_p, v_p));
}

int main(int argc, char*argv[]){

	init_planets();
	parse_options(argc,argv);
	init_misil(Cuerpos[3].x,Proyectil);

	int target_index = 3;
	int misil_index = Cuerpos.size()-1;

	Vn y(makeY());

	clog << "colisionando " << Cuerpos[misil_index].name << " contra " << Cuerpos[target_index].name << endl;
	pair<double,int> min(1e100,0);
	double span=.5;
	V3 pdir = Cuerpos[misil_index].v; //direccion inicial: derecho al target
	V3 mindir;
	while(min.first>1e-4){
		for(int ii=-1;ii<=1;ii++) for(int jj=-1;jj<=1;jj++){
			Cuerpos[misil_index].v=pdir.rotate(ii*span,jj*span); // Calculo direccion
			y=makeY(); // Rehago el vector y
			pair<double,int> nmin=mindist(y,misil_index,target_index);
			if(nmin.first<min.first){
				min=nmin;
				mindir=Cuerpos[misil_index].v;
			}
		}
		pdir=mindir;
		span*=.5;
		clog << "mindist: " << min.first << " span: " << span << " dir: " << pdir << " it: " << min.second << endl;
	}
	
	printNames();
	printPos(y);
	forn(iter,min.second/*resolution*/){
		y=NEXT(y);
		if(iter%(resolution/(outresolution-2))==0) printPos(y);
	}
	printPos(y);
	
	return 0;
}
