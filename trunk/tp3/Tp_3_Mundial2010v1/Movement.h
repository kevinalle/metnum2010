#ifndef _Movement_H
#define _Movement_H
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
#include <iostream>
#include <cassert>

/// movimiento del arquero
enum Movement { atRest, toLeft, toRight, invalid };
/// codifica a entero y manda a stream (ej archivo)
inline std::ostream & operator<<(std::ostream & os, const Movement & m)
{
	switch (m)
	{
	case atRest: os << 0; break;
	case toLeft: os << 1; break;
	case toRight: os << 2; break;
	case invalid:
	default: assert(false); os << -1000000; break;
	}
	return os;
}
/// decodifica desde entero tomado de stream (ej archivo)
inline std::istream & operator>>(std::istream & is, Movement & m)
{
	int mAsInt;
	if (is >> mAsInt)
		switch (mAsInt)
		{
		case 0: m = atRest; break;
		case 1: m = toLeft; break;
		case 2: m = toRight; break;
		default: assert(false); m = invalid; break;
		}
	return is;
}

/// para actualizar la posición del arquero
/**
Para no perder precisión, mantengo la posición del arquero 
en enteros: posición_real == halfWidth * posición_en_entero.
*/
inline int newPositionDelta(Movement state, Movement decision)
{
	switch (decision)
	{
	case atRest: return 0;
	case toLeft: return (state == toRight ? 0 : -1);
	case toRight: return (state == toLeft ? 0 : 1);
	}
	assert(false);
	return -1000000;
}
/// para actualizar el estado de movimiento del arquero
inline Movement newMovementState(Movement state, Movement decision)
{
	switch (decision)
	{
	case atRest: return atRest;
	case toLeft: return (state == toRight ? atRest : toLeft);
	case toRight: return (state == toLeft ? atRest : toRight);
	}
	assert(false);
	return invalid;
}

namespace {
/// el ancho del arquero
const double fullWidth = 0.1;
/// la mitad del ancho del arquero
const double halfWidth = fullWidth/2;
/// coordenada x del palo izquierdo
const double leftPost = -1.0;
/// coordenada x del palo derecho
const double rightPost = 1.0;
}

#endif