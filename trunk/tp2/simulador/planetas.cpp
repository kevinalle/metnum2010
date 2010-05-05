#include <vector>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <SDL/SDL.h>
using namespace std;

#include "Vector.h"

#define forn(i,n) for(int i=0;i<n;i++)
typedef vector<double> vd;
typedef vector<vd> vvd;

SDL_Surface* screen;

#define G 0.00002499215588275752801651213378056900054016

struct Planeta{
	Vector x;
	Vector v;
	double m;
	double r;
};

struct Observador{
	Vector pos;
	Vector dir;
	Vector up;
};

void draw_pixel32( SDL_Surface* S, int i, int j, Uint32 r, Uint32 g, Uint32 b ){
		//Convert the pixels to 32 bit
		Uint32* pixels = (Uint32*)S->pixels;
		//Set the pixel
		pixels[ (S->h-1-i)*S->w + j ] = SDL_MapRGB(S->format, r, g, b);
}

void clear(SDL_Surface* S, vvd& depth){
	forn(i,S->h) forn(j,S->w){
		//Convert the pixels to 32 bit
		Uint32* pixels = (Uint32*)S->pixels;
		//Set the pixel
		pixels[ i*S->w + j ] = SDL_MapRGB(S->format, 0, 0, 0);
		depth[i][j] = INFINITY;
	}
}

Vector Proyeccion( const Vector& p, const Observador& o ){
	// = Wp
	// las columnas de la matriz de proyeccion W
	// son las pryecciones de los vectores elementales

//	cout << o.dir*o.up << endl;
	assert(o.dir*o.up<0.001);

	const Vector& e1 = (o.dir^o.up).inverse().reflect(Vector(1,0,0));
	const Vector& e2 = o.dir.inverse().reflect(Vector(0,1,0)); // ?
	const Vector& e3 = o.up.inverse().reflect(Vector(0,0,1));

//	cout << e1 << e2 << e3 << endl;

	return Vector(
		e1.X()*p.X() + e2.X()*p.Y() + e3.X()*p.Z(),
		e1.Y()*p.X() + e2.Y()*p.Y() + e3.Y()*p.Z(),
		e1.Z()*p.X() + e2.Z()*p.Y() + e3.Z()*p.Z()
	);
}

void draw(SDL_Surface* S, vvd& depth, const Observador& o, const Vector& v, Uint32 r, Uint32 g, Uint32 b){
	Vector w = Proyeccion(v,o);
	int i = S->h/2 + w.Z();
	int j = S->w/2 + w.X();
	if(0<i && i<S->h && 0<j && j<S->w){
		if(w.Y() < depth[i][j]){
			depth[i][j] = w.Y();
			draw_pixel32(S,i,j,r,g,b);
		}
	}
}

void draw_base(SDL_Surface* S, vvd& depth, const Observador& o){
	forn(i,100) draw(S,depth,o,Vector(i,0,0),255,0,0);
//	forn(i,100) draw(S,depth,o,Vector(-i,0,0),255,0,0);

	forn(i,100) draw(S,depth,o,Vector(0,i,0),0,255,0);
//	forn(i,100) draw(S,depth,o,Vector(0,-i,0),0,255,0);

	forn(i,100) draw(S,depth,o,Vector(0,0,i),0,0,255);
//	forn(i,100) draw(S,depth,o,Vector(0,0,-i),0,0,255);
}

// fuerza ejercida sobre p1 por p2
Vector Fg(const Planeta& p1, const Planeta& p2){
	Vector F = -G*p1.m*p2.m*(p1.x-p2.x);
	double d = abs(pow((p1.x-p2.x).norm(),3.));
	return F/d;
}

int main(){

	/* inicio SDL */
	SDL_Surface* screen = NULL;
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return 1;

	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	if( !screen ) return 1;

	vvd depth(screen->h,vd(screen->w,INFINITY));

	// Coordenada (0,0): Solar System Barycenter
	// datos para: A.D. 2010-May-05 00:00:00.0000 CT
	// G = 6,67428 * 10^-11 * m^3 / (Kg*s^2)
	// = 0.00002499215588275752801651213378056900054016 * AU^3 / (1e-30*Kg * dia^2)
	// unidades:
	// * distancia: AU	= 149597870.691 km
	// * tiempo: dias	= 86400 s
	// * peso: 1.e-30 Kg

	Planeta sol;
	sol.x = Vector(-4.042895106228434e-03, 2.209532530800580e-03, 1.136425407067405e-05);	// AU
	sol.v = Vector(-1.786236608923230e-06, -5.959144368171789e-06, 4.287462284225408e-08);	// AU / dia
	sol.m = 1; // 10^30 Kg

	Planeta tierra;
	tierra.x = Vector(-7.262551982062518e-01, -7.016177342125620e-01, 2.942601923402196e-05);	// AU
	tierra.v = Vector(1.172032570433690e-02, -1.239499064419012e-02, -2.875393960566639e-07);	// AU / dia
	tierra.m = 1e-6; // 10^24 Kg = m_sol/10^6

	Planeta luna;
	luna.x = Vector(-7.248557601516714e-01, -7.039097848869444e-01, 1.029051462977911e-04);	// AU
	luna.v = Vector(1.220576787081027e-02, -1.211595432894550e-02, 4.775108508860639e-05);	// AU / dia
	luna.m = 1e-10; // 10^20 Kg = m_sol/10^10

	Observador o;
//	o.pos = Vector(0,0,0);
	o.dir = Vector(1,0,0).normalize();//o.pos.inverse().normalize();
	o.up = Vector(0,-1,0).normalize();

	clear(screen,depth);
	draw_base(screen,depth,o);
	SDL_Flip(screen);

	SDL_Event event;
	bool quit = false;
	while(!quit){

		while( SDL_PollEvent( &event ) ) {

			if( event.type == SDL_QUIT ) quit = true;

			if( event.type == SDL_KEYDOWN ) {

				switch( event.key.keysym.sym ) {
					case SDLK_q:
						quit = true;
						break;
					case SDLK_UP:
						o.dir = o.dir.rotate(0,-.1);
						o.up = o.up.rotate(0,-.1);
						clear(screen,depth);
						draw_base(screen,depth,o);
						break;
					case SDLK_DOWN:
						o.dir = o.dir.rotate(0,.1);
						o.up = o.up.rotate(0,.1);
						clear(screen,depth);
						draw_base(screen,depth,o);
						break;
					case SDLK_RIGHT:
						o.dir = o.dir.rotate(.1,0);
						o.up = o.up.rotate(.1,0);
						clear(screen,depth);
						draw_base(screen,depth,o);
						break;
					case SDLK_LEFT:
						o.dir = o.dir.rotate(-.1,0);
						o.up = o.up.rotate(-.1,0);
						clear(screen,depth);
						draw_base(screen,depth,o);
						break;
					default:
						break;
				}

			}
		}

		// fuerza gravitacional ejercida sobre p1 por p2:
		// Fg(p1,p2) = -G*m1*m2 * (x1-x2)/(|x1-x2|^3)

		Vector F_l = Fg(luna,tierra) + Fg(luna,sol);
		Vector F_t = Fg(tierra,sol) + Fg(tierra,luna);
		Vector F_s = Fg(sol,tierra) + Fg(sol,luna);

		Vector a_l = F_l/luna.m;
		Vector a_t = F_t/tierra.m;
		Vector a_s = F_s/sol.m;

		luna.v = luna.v + a_l;
		tierra.v = tierra.v + a_t;
		sol.v = sol.v + a_s;

		luna.x += luna.v;
		tierra.x += tierra.v;
		sol.x += sol.v;

		draw(screen,depth,o,luna.x,0,255,255);
		draw(screen,depth,o,tierra.x,255,255,255);
		draw(screen,depth,o,sol.x,255,255,0);

		cout << "ac luna: " << a_l << endl;
		cout << "ac tierra: " << a_t << endl;
		cout << "ac sol: " << a_s << endl;

		SDL_Flip(screen);

	}

	/* Quit SDL */
	SDL_Quit(); 

	return 0;
}
