#include "Matriz.h"

class ArqueroQueExtrapolaCM : public InterfazDeArquero
{
	public:
		void Inicializar();
		int Respuesta(int i);
		int Respuesta(int i, double x, double y);
	private:
		list<double> datos_i;
		list<double> datos_x;
		list<double> datos_y;
};

void ArqueroQueExtrapolaCM::Inicializar()
{
	datos_i.clear();
	datos_x.clear();
	datos_y.clear();
}

int ArqueroQueExtrapolaCM::Respuesta(int i)
{
	Mover(0);
	//cout << Posicion() << " " << 0 << " " << 0 << " "  << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << endl;
	return 0;
}

int ArqueroQueExtrapolaCM::Respuesta(int i, double x, double y)
{
	datos_i.push_back(i);
	datos_x.push_back(x);
	datos_y.push_back(y);

	if(datos_i.size()>=4)
	{	
		Matriz PX = CM(ToArray(datos_i),ToArray(datos_x),datos_i.size(),3);
		Matriz PY = CM(ToArray(datos_i),ToArray(datos_y),datos_i.size(),3);
	
		int t_gol = ProximaRaizDiscreta(PY,(int)datos_i.back());
		
		if(t_gol<0)
		{
			clog << "t_gol: " << t_gol << " la pelota no llega al arco!" << endl;
			Mover(0);
		}
		else
		{
			double x_gol = PN(PX,t_gol);
			Decidir(x_gol);
		}
		
		cout << Posicion() << " " << x << " " << y << " "  << PX(3,0) << " " << PX(2,0) << " " << PX(1,0) << " " << PX(0,0) << " " << PY(3,0) << " " << PY(2,0) << " " << PY(1,0) << " " << PY(0,0) << " " << endl;
	}
	
	return 0;
}
