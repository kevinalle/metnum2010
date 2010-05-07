#include <vector>
#include <cmath>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
using namespace std;

#include "Vector.h"

#define forn(i,n) for(int i=0;i<n;i++)
#define foreach(it,X) for(typeof((X).begin()) it=(X).begin();it!=(X).end();it++)
typedef vector<double> vd;
typedef vector<vd> vvd;

#include "Planetas.h"
#include "Timer.h"

SDL_Surface* screen;
TTF_Font* font;
vvd depth;

#define G 0.0002499215588275752801651213378056900054016

struct Observador{
	Vector off;
	Vector dir;
	Vector up;
};

void draw_pixel32( SDL_Surface* S, int i, int j, Uint32 r, Uint32 g, Uint32 b ){
		//Convert the pixels to 32 bit
		Uint32* pixels = (Uint32*)S->pixels;
		//Set the pixel
		pixels[ (S->h-1-i)*S->w + j ] = SDL_MapRGB(S->format, r, g, b);
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
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

//	assert(o.dir*o.up<0.001);

	const Vector& e1 = (o.dir^o.up);
	const Vector& e2 = o.dir.inverse();
	const Vector& e3 = o.up.inverse();

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
	forn(i,50) draw(S,o,Vector(i,0,0),100,0,0);
	forn(i,50) draw(S,o,Vector(0,i,0),0,100,0);
	forn(i,50) draw(S,o,Vector(0,0,i),0,0,100);
}

Vector Fg(const Planeta& p1, const Planeta& p2){
	// fuerza ejercida sobre p1 por p2
	// Fg(p1,p2) = -G*m1*m2 * (x1-x2)/(|x1-x2|^3)
	Vector F = -G*p1.m*p2.m*(p1.x-p2.x);
	double d = abs(pow((p1.x-p2.x).norm(),3));
	return F/d;
}

void draw_orbits(list<Vector>& orbitas){

	ifstream f_sol; f_sol.open("sol.in");
	ifstream f_mercurio; f_mercurio.open("mercurio.in");
	ifstream f_venus; f_venus.open("venus.in");
	ifstream f_tierra; f_tierra.open("tierra.in");
	ifstream f_luna; f_luna.open("luna.in");
	ifstream f_marte; f_marte.open("marte.in");
	ifstream f_jupiter; f_jupiter.open("jupiter.in");
	ifstream f_saturno; f_saturno.open("saturno.in");

	forn(i,3000){
		double x, y, z; Vector X;
		f_sol >> x >> y >> z; X = Vector(x,y,z);
		f_sol >> x >> y >> z;
		orbitas.push_back(X);
		f_mercurio >> x >> y >> z; X = Vector(x,y,z);
		f_mercurio >> x >> y >> z;
		orbitas.push_back(X);
		f_venus >> x >> y >> z; X = Vector(x,y,z);
		f_venus >> x >> y >> z;
		orbitas.push_back(X);
		f_tierra >> x >> y >> z; X = Vector(x,y,z);
		f_tierra >> x >> y >> z;
		orbitas.push_back(X);
		f_luna >> x >> y >> z; X = Vector(x,y,z);
		f_luna >> x >> y >> z;
		orbitas.push_back(X);
		f_marte >> x >> y >> z; X = Vector(x,y,z);
		f_marte >> x >> y >> z;
		orbitas.push_back(X);
		f_jupiter >> x >> y >> z; X = Vector(x,y,z);
		f_jupiter >> x >> y >> z;
		orbitas.push_back(X);
		f_saturno >> x >> y >> z; X = Vector(x,y,z);
		f_saturno >> x >> y >> z;
		orbitas.push_back(X);
	}

	f_sol.close();
	f_mercurio.close();
	f_venus.close();
	f_tierra.close();
	f_luna.close();
	f_marte.close();
	f_jupiter.close();
	f_saturno.close();
}

bool init(){
	/* inicio SDL */
	SDL_Surface* screen = NULL;

	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
	if( TTF_Init()==-1 ) return false;

	font = TTF_OpenFont( "/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 20); // /usr/share/fonts/truetype/latex-xft-fonts/cmr10.ttf
	if( font == NULL ) return false;

	SDL_WM_SetCaption("Orbit Sim",NULL);

	return true;
}

int main(){

	if( !init() ) return 1;

	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE/*|SDL_FULLSCREEN*/);
	if( !screen ) return 1;

	depth = vvd(screen->h,vd(screen->w,INFINITY));

	// inicializa la info de los planetas y la list<Planeta> 'planetas'
	initPlanetas();

/************************************************************/

	/* Para toquetear */

	// tiempo virtual de simulacion (en dias)
	double total_sim_t = 1000000;//365;

	// delta de tiempo (en dias)
	double dt = .1;//.04;

	// tiempo real de simulacion en frames/s
	// 1 dias/dt = 1 frame
	int fps = 30;

	// zoom sobre el espacio
	double zoom = 20;

/************************************************************/

	list<Vector> orbitas;
	draw_orbits(orbitas);

	Observador o;
	o.off = Vector(0,0,0);
	o.dir = Vector(0,0,-1).normalize();
	o.up = Vector(0,1,0).normalize();

	Timer t;
	SDL_Event event;
	double sim_t = 0; // en 1/dt * dias
	bool quit = false;
	bool moving = false;
	bool sim_stop = true;
	bool sim_pause = false;
	int mouseX, mouseY;
	while(!quit){

		t.start();

		/* EVENTOS */

			while( SDL_PollEvent( &event ) ) {

				if( event.type == SDL_QUIT ) quit = true;

				if( event.type == SDL_KEYDOWN ) {

					switch( event.key.keysym.sym ) {
						case SDLK_q:
							quit = true;
							break;
						case SDLK_s:
							if(sim_stop){
								sim_t = 0;
								foreach(it,planetas) it->orbit.clear();
							}
							sim_pause = false;
							sim_stop = !sim_stop;
							break;
						case SDLK_PLUS:
							zoom += 5;
							break;
						case SDLK_MINUS:
							zoom -= 5;
							if(!zoom) zoom = 5;
							break;
						case SDLK_p:
							if(!sim_stop) sim_pause = !sim_pause;
							break;
						case SDLK_UP:
							o.off -= 10*o.up;
							break;
						case SDLK_DOWN:
							o.off += 10*o.up;
							break;
						case SDLK_RIGHT:
							o.off += 10*(o.dir^o.up);
							break;
						case SDLK_LEFT:
							o.off -= 10*(o.dir^o.up);
							break;
						default:
							break;
					}

				}

				if( event.type == SDL_MOUSEBUTTONDOWN ){
					if( event.button.button == SDL_BUTTON_MIDDLE ){
						mouseX = event.button.x;
						mouseY = event.button.y;
						moving = true;
					}
					if( event.button.button == SDL_BUTTON_WHEELUP ) zoom += 5;
					if( event.button.button == SDL_BUTTON_WHEELDOWN ){
						zoom -= 5;
						if(!zoom) zoom = 5;
					}
				}

				if( event.type == SDL_MOUSEBUTTONUP ){
					if( event.button.button == SDL_BUTTON_MIDDLE )
						moving = false;
				}

				if( event.type == SDL_MOUSEMOTION ){
					if(moving){
						int newX = event.motion.x;
						int newY = event.motion.y;
						int dX = newX - mouseX;
						int dY = newY - mouseY;
						mouseX = newX;
						mouseY = newY;

						o.dir = o.dir.rotate(-.01*dX,0);
						o.up = o.up.rotate(-.01*dX,0);
						o.dir = o.dir.rotate(0,-.01*dY);
						o.up = o.up.rotate(0,-.01*dY);
					}
				}

			}

		/* RENDER */

			clear(screen);
			draw_base(screen,o);
			foreach(it,planetas) foreach(p,it->orbit) draw(screen,o,zoom*(*p),it->r,it->g,it->b);
			foreach(it,orbitas) draw(screen,o,zoom*(*it),100,100,100);

			stringstream s, s2;
			s << (sim_stop ? "Stopped" : ( sim_pause ? "Paused" : "Playing" ));
			s2 << "Epoch: " << (int)sim_t << " dias";

			SDL_Surface *message = TTF_RenderText_Solid(font, s.str().c_str(), (sim_stop ? SDL_Color({255,0,0,0}) : ( sim_pause ? SDL_Color({0,0,255,0}) : SDL_Color({0,255,0,0}) )) );
			apply_surface(5,0,message,screen);

			message = TTF_RenderText_Solid(font, s2.str().c_str(), {255,255,255,0} );
			apply_surface(5,20,message,screen);

			SDL_FreeSurface( message );

			if( SDL_Flip(screen)==-1 ) return 1;

		/* SIMULACION */

			if(sim_t > total_sim_t) sim_stop = true;

			if(!sim_stop && !sim_pause){

				foreach(it,planetas){

					Vector a(0,0,0);

					// Fg = fuerza gravitacional ejercida sobre p1 por p2:
					foreach(it2,planetas) if(it!=it2) a += Fg(*it,*it2);

					a /= it->m;
					it->v += dt*a;
					it->x += dt*it->v;

					// esto es reindio
					it->orbit.push_back(it->x);
				}

				sim_t += dt;
			}

		/* FRAME RATE */

			// bloqueo hasta cumplir el framerate
			if (t.get_ticks() < 1000/fps) SDL_Delay((1000/fps)-t.get_ticks());
	}

	// cleanup
	TTF_CloseFont( font );
	TTF_Quit();
	SDL_Quit(); 

	return 0;
}
