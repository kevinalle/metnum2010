#include "InterfazDeArquero.h"
#include "algoritmos.h"

#define GRADO 6

class Arquero : public InterfazDeArquero
{
	public:
		void Inicializar();
		int Respuesta(int i);
		int Respuesta(int i, double x, double y);
	private:
		list<double> datos_i;
		list<double> datos_x;
		list<double> datos_y;
		
		int Extrapolar(const Matriz& PX, const Matriz& PY);
		int ComputarRespuesta(int i);
		void Print(const Matriz& PX, const Matriz& PY);
};

void Arquero::Inicializar()
{
	datos_i.clear();
	datos_x.clear();
	datos_y.clear();
}

void Arquero::Print(const Matriz& PX, const Matriz& PY)
{
	cout<<Posicion()<<" "<<datos_x.back()<<" "<<datos_y.back()<<" ";
	int n=PX.Filas();
	forn(i,n) cout << PX(n-i-1,0) << " ";
	forn(i,3-n) cout << 0 << " ";
	forn(i,n) cout << PY(n-i-1,0) << " ";
	forn(i,3-n) cout << 0 << " ";
	//cout << endl;
}

int Arquero::Respuesta(int i)
{
	return ComputarRespuesta(i);
}

int Arquero::Respuesta(int i, double x, double y)
{
	if(datos_i.size()) forsn(j,datos_i.back()+1,i)
		//clog << ComputarRespuesta(j) << endl;
		ComputarRespuesta(j);
	
	datos_i.push_back(i);
	datos_x.push_back(x);
	datos_y.push_back(y);

	return ComputarRespuesta(i);
}

int Arquero::Extrapolar(const Matriz& PX, const Matriz& PY)
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

int Arquero::ComputarRespuesta(int i)
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
	else if(n<3)
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
		int grado = min(GRADO,n);
		// Aproximo las  funciones por cuadrados mínimos de grado GRADO
		Matriz PX = CM(ToArray(datos_i),ToArray(datos_x),datos_i.size(),grado);
		Matriz PY = CM(ToArray(datos_i),ToArray(datos_y),datos_i.size(),grado);
		
		// Calculo los GRADO ultimos puntos en los polinomios aproximados
		double i5[grado]; forrn(k,grado) i5[k] = i-k;
		double xs[grado]; forn(k,grado) xs[k] = Pn(PX,i5[k]);
		double ys[grado]; forn(k,grado) ys[k] = Pn(PY,i5[k]);
		
		// Aproximo los GRADO ultimos puntos por una cuadratica con CM
		Matriz PX2 = CM(i5,xs,grado,2);
		Matriz PY2 = CM(i5,ys,grado,2);
		
		Print(PX2,PY2);
		res=Extrapolar(PX2,PY2);
	}
	return res;
}
