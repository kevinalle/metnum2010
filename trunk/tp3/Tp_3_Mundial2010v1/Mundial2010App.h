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

#ifndef _MUNDIAL2010APP_H_
#define _MUNDIAL2010APP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "MainDialog.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * Mundial2010App class declaration
 */

class Mundial2010App: public wxApp
{    
    DECLARE_CLASS( Mundial2010App )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    Mundial2010App();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin Mundial2010App event handler declarations

////@end Mundial2010App event handler declarations

////@begin Mundial2010App member function declarations

////@end Mundial2010App member function declarations

////@begin Mundial2010App member variables
////@end Mundial2010App member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(Mundial2010App)
////@end declare app

#endif
    // _MUNDIAL2010APP_H_
