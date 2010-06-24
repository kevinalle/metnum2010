#include "Matriz.h"

class ArqueroQueExtrapolaCM : public InterfazDeArquero
{
	public:
		void Inicializar();
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

int ArqueroQueExtrapolaCM::Respuesta(int i, double x, double y)
{
	datos_i.push_back(i);
	datos_x.push_back(x);
	datos_y.push_back(y);

	if(datos_i.size()>=4)
	{
		Matriz PX = CM(ToArray(datos_i),ToArray(datos_x),datos_i.size(),3);
		Matriz PY = CM(ToArray(datos_i),ToArray(datos_y),datos_i.size(),3);
	
		cout << PX << endl;
		cout << PY << endl;
	}
	
	return 0;
}
