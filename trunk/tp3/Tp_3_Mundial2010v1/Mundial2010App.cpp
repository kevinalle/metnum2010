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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "Mundial2010App.h"

////@begin XPM images
////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( Mundial2010App )
////@end implement app


/*!
 * Mundial2010App type definition
 */

IMPLEMENT_CLASS( Mundial2010App, wxApp )


/*!
 * Mundial2010App event table definition
 */

BEGIN_EVENT_TABLE( Mundial2010App, wxApp )

////@begin Mundial2010App event table entries
////@end Mundial2010App event table entries

END_EVENT_TABLE()


/*!
 * Constructor for Mundial2010App
 */

Mundial2010App::Mundial2010App()
{
    Init();
}


/*!
 * Member initialisation
 */

void Mundial2010App::Init()
{
////@begin Mundial2010App member initialisation
////@end Mundial2010App member initialisation
}

/*!
 * Initialisation for Mundial2010App
 */

bool Mundial2010App::OnInit()
{    
////@begin Mundial2010App initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	MainDialog* mainWindow = new MainDialog(NULL, ID_MAINDIALOG, wxGetTranslation(wxString(wxT("M")) + (wxChar) 0x00E9 + wxT("todos Num") + (wxChar) 0x00E9 + wxT("ricos 2010c1 - TP3 - Probador")));
	/* int returnValue = */ mainWindow->ShowModal();

	mainWindow->Destroy();
	// A modal dialog application should return false to terminate the app.
	return false;
////@end Mundial2010App initialisation

    return true;
}


/*!
 * Cleanup for Mundial2010App
 */

int Mundial2010App::OnExit()
{    
////@begin Mundial2010App cleanup
	return wxApp::OnExit();
////@end Mundial2010App cleanup
}

