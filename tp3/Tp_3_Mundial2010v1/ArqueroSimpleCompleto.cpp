/** \file

\author Pablo Haramburu
Copyright: 
	Copyright (C)2010 Pablo Haramburu.
License: 
	This file is part of mundial2010.

	mundial2010 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mundial2010 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mundial2010.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "GoalkeeperBase.h"
#include "Movement.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#define _(x) x


class Goalkeeper : public GoalkeeperBase
{
public:
	Movement computeResponse(int meassurement, double x, double y);
	/// para mediciones faltantes
	Movement computeResponse(int meassurement);
};
Movement Goalkeeper::computeResponse(int meassurement, double x, double y)
{
	Movement move = atRest;
	double pos = position();

	if ( fabs(pos-x) <= fullWidth )
		move = atRest;
	else if ( pos > x && pos > leftPost )
		move = toLeft;
	else if ( pos < x && pos < rightPost )
		move = toRight;

	update(move);

	return move;
}
Movement Goalkeeper::computeResponse(int meassurement)
{
	Movement move = atRest;
	update(move);
	return move;
}


int main(int argc, char **argv)
{
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

	Goalkeeper gk;

	int meassurement; int i=1;
	while ((input >> meassurement) && meassurement != -1) {
		for(; i<meassurement; ++i)
			output << i << ' ' << gk.computeResponse(i) << std::endl;
		double x, y;
		input >> x >> y;
		assert(i==meassurement);
		output << i << ' ' << gk.computeResponse(i, x, y) << std::endl;
		++i;
	}
	return 0;
}
 
