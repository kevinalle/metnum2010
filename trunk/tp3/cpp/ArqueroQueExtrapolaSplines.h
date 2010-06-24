#include "algoritmos.h"
#include "InterfazDeArquero.h"

class ArqueroQueExtrapolaSplines : public InterfazDeArquero
{
	public:
		void Inicializar();
		int Respuesta(int i, double x, double y);
	private:
		list<Punto> datos_x;
		list<Punto> datos_y;
};

void ArqueroQueExtrapolaSplines::Inicializar()
{
	datos_x.clear();
	datos_y.clear();
}

int ArqueroQueExtrapolaSplines::Respuesta(int i, double x, double y)
{
	datos_x.push_back(Punto(i,x));
	datos_y.push_back(Punto(i,y));
	
	if(datos_x.size()>=3)
	{
		int n = datos_x.size();

		Spline* PX = GenerarSpline(ToArray(datos_x),n);
		Spline* PY = GenerarSpline(ToArray(datos_y),n);
		
		int t_gol = ProximaRaizDiscreta(PX[n-2],datos_y.back().x);
		if(t_gol<0)
		{
			clog << "la pelota no llega al arco!" << endl;
			Mover(0);
		}
		else
		{
			double x_gol = P3(PX[n-2],t_gol);
			//cout << "x_gol: " << x_gol << endl;
			
			if (x_gol > Posicion())
				Mover(1);
			else if (x_gol < Posicion())
				Mover(-1);
			else
				Mover(0);
		}
		
		delete[] PX;
		delete[] PY;
		
		cout << Posicion() << " " << x << " " << y << " " << PX[n-2] << " " << PY[n-2] << endl;
		
		return UltimaDireccion() + 1;
	}
	return 1;
}
