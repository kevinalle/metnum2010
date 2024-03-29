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

// Generated by DialogBlocks (unregistered), 01/06/2010 01:49:44

#ifndef _TESTRESULTSDIALOG_H_
#define _TESTRESULTSDIALOG_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/listctrl.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxListCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_TESTRESULTSDIALOG 10006
#define ID_LISTCTRL1 10007
#define ID_LISTCTRL2 10008
#define SYMBOL_TESTRESULTSDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_TESTRESULTSDIALOG_TITLE _("Resultado de las pruebas")
#define SYMBOL_TESTRESULTSDIALOG_IDNAME ID_TESTRESULTSDIALOG
#define SYMBOL_TESTRESULTSDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_TESTRESULTSDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * TestResultsDialog class declaration
 */

class TestResultsDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( TestResultsDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    TestResultsDialog();
    TestResultsDialog( wxWindow* parent, wxWindowID id = SYMBOL_TESTRESULTSDIALOG_IDNAME, const wxString& caption = SYMBOL_TESTRESULTSDIALOG_TITLE, const wxPoint& pos = SYMBOL_TESTRESULTSDIALOG_POSITION, const wxSize& size = SYMBOL_TESTRESULTSDIALOG_SIZE, long style = SYMBOL_TESTRESULTSDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_TESTRESULTSDIALOG_IDNAME, const wxString& caption = SYMBOL_TESTRESULTSDIALOG_TITLE, const wxPoint& pos = SYMBOL_TESTRESULTSDIALOG_POSITION, const wxSize& size = SYMBOL_TESTRESULTSDIALOG_SIZE, long style = SYMBOL_TESTRESULTSDIALOG_STYLE );

    /// Destructor
    ~TestResultsDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin TestResultsDialog event handler declarations

////@end TestResultsDialog event handler declarations

////@begin TestResultsDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end TestResultsDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin TestResultsDialog member variables
    wxListCtrl* m_results;
    wxListCtrl* m_summary;
    wxButton* m_cancelBtn;
////@end TestResultsDialog member variables
};

#endif
    // _TESTRESULTSDIALOG_H_
