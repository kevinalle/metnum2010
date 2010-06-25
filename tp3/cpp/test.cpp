#include "algoritmos.h"
//#include "ArqueroQueExtrapolaSplines.h"
//#include "ArqueroQueExtrapolaCM.h"
#include "Arquero.h"

int main()
{
	//ArqueroQueExtrapolaSplines arquero;
	//ArqueroQueExtrapolaCM arquero;
	Arquero arquero;
	arquero.Inicializar();
	int i; double x, y;
	while( cin >> i && i!=-1 )
	{
		cin >> x >> y;
		//clog << arquero.Respuesta(i,x,y) << endl;
		arquero.Respuesta(i,x,y);
	}
	if( abs(x-arquero.Posicion())<.05 )
		clog << "ATAJO!" << endl;
	else
		clog << "GOL! a distancia: " << abs(x-arquero.Posicion()) << endl;
	return 0;
}
