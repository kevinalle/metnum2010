#include "InterfazDeArquero.h"
#include "algoritmos.h"

#define GRADO 6

class ArqueroLoco : public InterfazDeArquero
{
	public:
		void Inicializar();
		int Respuesta(int i, double x, double y);
	private:
		list<double> datos_i;
		list<double> datos_x;
		list<double> datos_y;
		
		int Respuesta(int i);
		int Extrapolar(const Matriz& PX, const Matriz& PY);
		int ComputarRespuesta(int i);
		void Print(const Matriz& PX, const Matriz& PY);
};

void ArqueroLoco::Inicializar()
{
	datos_i.clear();
	datos_x.clear();
	datos_y.clear();
}

void ArqueroLoco::Print(const Matriz& PX, const Matriz& PY)
{
	cout<<Posicion()<<" "<<datos_x.back()<<" "<<datos_y.back()<<" ";
	int n=PX.Filas();
	forn(i,n) cout << PX(n-i-1,0) << " ";
	forn(i,3-n) cout << 0 << " ";
	forn(i,n) cout << PY(n-i-1,0) << " ";
	forn(i,3-n) cout << 0 << " ";
	//cout << endl;
}

int ArqueroLoco::Respuesta(int i)
{
	return ComputarRespuesta(i);
}

int ArqueroLoco::Respuesta(int i, double x, double y)
{
	if(datos_i.size()) forsn(j,datos_i.back()+1,i)
		//clog << ComputarRespuesta(j) << endl;
		ComputarRespuesta(j);
	
	datos_i.push_back(i);
	datos_x.push_back(x);
	datos_y.push_back(y);

	return ComputarRespuesta(i);
}

int ArqueroLoco::Extrapolar(const Matriz& PX, const Matriz& PY)
{
	// Calculo el instante del gol, cuando y~0
	int t_gol = ProximaRaizDiscreta(PY,(int)datos_i.back());
	
	if(t_gol<0)
	{
		cout << 0 << endl;
		//clog << "t_gol: " << t_gol << " la pelota no llega al arco!" << endl;
		Mover(0);
		return 0;
	}
	else
	{
		// Calculo la posicion de la pelota en el instante del gol
		double x_gol = Pn(PX,t_gol);
		cout << x_gol << endl;
		// Decido para donde me muevo
		return Decidir(x_gol);
	}
}

int ArqueroLoco::ComputarRespuesta(int i)
{
	int n = datos_i.size();
	int res = 0;
	if(n<2)
	{
		// Me quedo quieto, no puedo deducir mucho
		Mover(0);
		Print(Matriz(0,0),Matriz(0,0));
		res = 0;
	}
	else if(n==2)
	{
		// an ... a0
		// Extrapolo la recta que pasa por ambos puntos
		Matriz PX = Recta(datos_i.front(),datos_x.front(),datos_i.back(),datos_x.back());
		Matriz PY = Recta(datos_i.front(),datos_y.front(),datos_i.back(),datos_y.back());
		
		Print(PX,PY);
		res=Extrapolar(PX,PY);
	}
	else if(2<n && n<GRADO)
	{
		// an ... a0
		// Extrapolo por CM comun de grado i-1
		Matriz PX = CM(ToArray(datos_i),ToArray(datos_x),datos_i.size(),i-1);
		Matriz PY = CM(ToArray(datos_i),ToArray(datos_y),datos_i.size(),i-1);

		Print(PX,PY);
		res=Extrapolar(PX,PY);
	}
	else
	{
		// Aproximo las  funciones por cuadrados mínimos de grado GRADO
		Matriz PX = CM(ToArray(datos_i),ToArray(datos_x),datos_i.size(),GRADO);
		Matriz PY = CM(ToArray(datos_i),ToArray(datos_y),datos_i.size(),GRADO);
		
		// Calculo los 6 ultimos puntos en los polinomios aproximados
		double i6[6] = { i-5 , i-4 , i-3 , i-2 , i-1 , i };
		double x6[6]; forn(k,6) x6[k] = Pn(PX,i6[k]);
		double y6[6]; forn(k,6) y6[k] = Pn(PY,i6[k]);
		
		// Aproximo los 5 ultimos puntos por una cuadratica con CM
		Matriz PX2 = CM(i6,x6,6,2);
		Matriz PY2 = CM(i6,y6,6,2);
		
		// Calculo los 6 ultimos puntos en los polinomios aproximados
		double xx6[6]; forn(k,6) xx6[k] = Pn(PX2,i6[k]);
		double yy6[6]; forn(k,6) yy6[k] = Pn(PY2,i6[k]);
		
		// Calculo los 6-1 splines interpolantes
		Spline* Sx = GenerarSpline(i6,xx6,6);
		Spline* Sy = GenerarSpline(i6,yy6,6);
		
		// Extrapolo el anteultimo
		Matriz SPx = SplineAMatriz(Sx[4]);
		Matriz SPy = SplineAMatriz(Sy[4]);
		
		Print(SPx,SPy);
		res=Extrapolar(SPx,SPy);
	}
	return res;
}
