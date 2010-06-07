#ifndef _GoalkeeperBase_H
#define _GoalkeeperBase_H
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

#include "Movement.h"

/// clase base con algunas funciones útiles
class GoalkeeperBase
{
public:
	GoalkeeperBase() : m_position(0), m_state(atRest) {}
public:
	double position() const { return halfWidth * m_position; }
	void update(Movement move) 
	{ 
		m_position += newPositionDelta(m_state, move);
		m_state = newMovementState(m_state, move);
	}
protected:
	/**
	Para no perder precisión, mantengo la posición del arquero 
	en enteros: posición_real == halfWidth * posición_en_entero.
	*/
	int m_position;
	Movement m_state;
};

#endif