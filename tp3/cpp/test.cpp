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
	int i_anterior=10000; // INF
	while( cin >> i && i!=-1 )
	{
		forsn(j,i_anterior+1,i)
			clog << arquero.Respuesta(i) << endl;
		cin >> x >> y;
		clog << arquero.Respuesta(i,x,y) << endl;
		i_anterior=i;
	}
	return 0;
}
