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
		clog << arquero.Respuesta(i,x,y) << endl;
	}
	return 0;
}
