#include <vector>
#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <SDL/SDL.h>
using namespace std;

#include "Vector.h"

#define forn(i,n) for(int i=0;i<n;i++)
#define foreach(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)
typedef vector<double> vd;
typedef vector<vd> vvd;

#include "Planetas.h"
#include "Timer.h"

SDL_Surface* screen;
vvd depth;

#define G 0.0002499215588275752801651213378056900054016

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

void clear(SDL_Surface* S){
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

void draw(SDL_Surface* S, const Observador& o, const Vector& v, Uint32 r, Uint32 g, Uint32 b){
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

void draw_base(SDL_Surface* S, const Observador& o){
	forn(i,100) draw(S,o,Vector(i,0,0),255,0,0);
//	forn(i,100) draw(S,depth,o,Vector(-i,0,0),255,0,0);

	forn(i,100) draw(S,o,Vector(0,i,0),0,255,0);
//	forn(i,100) draw(S,depth,o,Vector(0,-i,0),0,255,0);

	forn(i,100) draw(S,o,Vector(0,0,i),0,0,255);
//	forn(i,100) draw(S,depth,o,Vector(0,0,-i),0,0,255);
}

// fuerza ejercida sobre p1 por p2
// Fg(p1,p2) = -G*m1*m2 * (x1-x2)/(|x1-x2|^3)
Vector Fg(const Planeta& p1, const Planeta& p2){
	Vector F = -G*p1.m*p2.m*(p1.x-p2.x);
	double d = abs(pow((p1.x-p2.x).norm(),3));
	return F/d;
}

int main(){

	/* inicio SDL */
	SDL_Surface* screen = NULL;
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return 1;

	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	if( !screen ) return 1;

	depth = vvd(screen->h,vd(screen->w,INFINITY));

	// inicializa la info de los planetas y la list<Planeta> 'planetas'
	initPlanetas();

/************************************************************/

	/* Para toquetear */

	// tiempo virtual de simulacion (en dias)
	double total_sim_t = 1000000;

	// delta de tiempo (en dias)
	double dt = 1;

	// tiempo real de simulacion en frames/s
	// 1 dias/dt = 1 frame
	int fps = 365;

	// zoom sobre el espacio
	double zoom = 20;

/************************************************************/

	Observador o;
//	o.pos = Vector(0,0,0);
	o.dir = Vector(0,0,1).normalize();//o.pos.inverse().normalize();
	o.up = Vector(0,-1,0).normalize();

	clear(screen);
	draw_base(screen,o);
	SDL_Flip(screen);

	Timer t;
	SDL_Event event;
	int sim_t = 0; // en 1/dt * dias
	bool quit = false;
	while(!quit){

		t.start();

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
						clear(screen);
						draw_base(screen,o);
						break;
					case SDLK_DOWN:
						o.dir = o.dir.rotate(0,.1);
						o.up = o.up.rotate(0,.1);
						clear(screen);
						draw_base(screen,o);
						break;
					case SDLK_RIGHT:
						o.dir = o.dir.rotate(.1,0);
						o.up = o.up.rotate(.1,0);
						clear(screen);
						draw_base(screen,o);
						break;
					case SDLK_LEFT:
						o.dir = o.dir.rotate(-.1,0);
						o.up = o.up.rotate(-.1,0);
						clear(screen);
						draw_base(screen,o);
						break;
					default:
						break;
				}

			}
		}

		if(sim_t<=total_sim_t/dt){

			foreach(it,planetas){

				draw(screen,o,zoom*it->x,it->r,it->g,it->b);

				Vector a(0,0,0);

				// Fg = fuerza gravitacional ejercida sobre p1 por p2:
				foreach(it2,planetas) if(it!=it2) a += Fg(*it,*it2);

				a /= it->m;
				it->v += dt*a;
				it->x += dt*it->v;

			}
			SDL_Flip(screen);
		}

		sim_t++;

		// bloqueo hasta cumplir el framerate
		if (t.get_ticks() < 1000/fps) SDL_Delay((1000/fps) - t.get_ticks());

	}

	/* Quit SDL */
	SDL_Quit(); 

	return 0;
}
