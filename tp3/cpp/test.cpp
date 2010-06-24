#include <list>
#include <iostream>
using namespace std;

#include "Arquero.h"

int main()
{
	/*list<Punto> datos;
	int i; double x, y;
	while( cin >> i && i!=-1 )
	{
		cin >> x >> y;
		datos.push_back(Punto(x,y));
	}
	Punto* A = ToArray(datos);
	Spline* P = GenerarSpline(A,datos.size());
	forn(i,(int)datos.size()-1)
		cout << i << ": " << P[i] << endl;*/
	Arquero arquero;
	arquero.Inicializar();
	int i; double x, y;
	while( cin >> i && i!=-1 )
	{
		cin >> x >> y;
		cout << arquero.Respuesta(i,x,y) << endl;
	}
	return 0;
}
