#include "algoritmos.h"
//#include "ArqueroQueExtrapolaSplines.h"
//#include "ArqueroQueExtrapolaCM.h"
#include "Arquero.h"
//#include "ArqueroLoco.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#define _(x) x


int main(int argc, char **argv){
    if ( argc < 3 )
        return 1;

	std::ifstream input(argv[1]);
	if (!input) {
		std::cerr << _("No se pudo abrir el archivo de entrada!") << std::endl;
		return 2;
	}

	std::ofstream output(argv[2]);
	if (!output) {
		std::cerr << _("No se pudo crear el archivo de salida!") << std::endl;
		return 3;
	}

	Arquero gk;

	int meassurement; int i=1;
	while ((input >> meassurement) && meassurement != -1) {
		for(; i<meassurement; ++i)
			output << i << ' ' << gk.Respuesta(i) << std::endl;
		double x, y;
		input >> x >> y;
		assert(i==meassurement);
		output << i << ' ' << gk.Respuesta(i, x, y) << std::endl;
		++i;
	}
	return 0;
}
 
