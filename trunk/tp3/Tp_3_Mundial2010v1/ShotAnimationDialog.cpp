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

// Generated by DialogBlocks (unregistered), 04/06/2010 13:42:38

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

#include "ShotAnimationDialog.h"
#include "Movement.h"
#include <cassert>
#include <algorithm>
#include <vector>
#include <limits>

////@begin XPM images
////@end XPM images


/*!
 * ShotAnimationDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ShotAnimationDialog, wxDialog )


/*!
 * ShotAnimationDialog event table definition
 */

BEGIN_EVENT_TABLE( ShotAnimationDialog, wxDialog )

////@begin ShotAnimationDialog event table entries
////@end ShotAnimationDialog event table entries
	EVT_TIMER(wxID_ANY, ShotAnimationDialog::OnTimer)

END_EVENT_TABLE()


/*!
 * ShotAnimationDialog constructors
 */

ShotAnimationDialog::ShotAnimationDialog()
{
    Init();
}

ShotAnimationDialog::ShotAnimationDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * ShotAnimationDialog creator
 */

bool ShotAnimationDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin ShotAnimationDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end ShotAnimationDialog creation
    return true;
}


/*!
 * ShotAnimationDialog destructor
 */

ShotAnimationDialog::~ShotAnimationDialog()
{
////@begin ShotAnimationDialog destruction
////@end ShotAnimationDialog destruction
}


/*!
 * Member initialisation
 */

void ShotAnimationDialog::Init()
{
////@begin ShotAnimationDialog member initialisation
    m_goalkeeper = NULL;
    m_testfile = NULL;
    m_theField = NULL;
    m_cancelBtn = NULL;
////@end ShotAnimationDialog member initialisation

	m_timer.SetOwner(this);
	m_currentStep = 0;
}


/*!
 * Control creation for ShotAnimationDialog
 */

void ShotAnimationDialog::CreateControls()
{    
////@begin ShotAnimationDialog content construction
    // Generated by DialogBlocks, 04/06/2010 17:10:06 (unregistered)

    ShotAnimationDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Arquero:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_goalkeeper = new wxTextCtrl( itemDialog1, ID_GOALKEEPER_TEXTCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemBoxSizer3->Add(m_goalkeeper, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Test:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_testfile = new wxTextCtrl( itemDialog1, ID_TESTFILE_TEXTCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemBoxSizer3->Add(m_testfile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_theField = new wxPanel( itemDialog1, ID_THE_FIELD_PANEL, wxDefaultPosition, wxSize(300, 300), wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_theField->SetBackgroundColour(wxColour(160, 224, 160));
    itemBoxSizer2->Add(m_theField, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer9, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_OK, _("&Siguiente Test"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemButton10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_cancelBtn = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(m_cancelBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Connect events and objects
    m_theField->Connect(ID_THE_FIELD_PANEL, wxEVT_SIZE, wxSizeEventHandler(ShotAnimationDialog::OnSize), NULL, this);
    m_theField->Connect(ID_THE_FIELD_PANEL, wxEVT_PAINT, wxPaintEventHandler(ShotAnimationDialog::OnPaint), NULL, this);
////@end ShotAnimationDialog content construction
}


/*!
 * Should we show tooltips?
 */

bool ShotAnimationDialog::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap ShotAnimationDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin ShotAnimationDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end ShotAnimationDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon ShotAnimationDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin ShotAnimationDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end ShotAnimationDialog icon retrieval
}

class CoordMapper
{
public:
	static const double xMin;
	static const double xMax;
	static const double yMin;
	static const double yMax;
	CoordMapper(wxSize sz) : m_size(sz) {}
	wxPoint toDc(double x, double y)
	{
		return wxPoint(
			(x-xMin)/(xMax-xMin)*m_size.GetWidth()+0.5,
			(y-yMin)/(yMax-yMin)*m_size.GetHeight()+0.5); //0.5 == redondear
	}
private:
	wxSize m_size;
};
const double CoordMapper::xMin = -5.0;
const double CoordMapper::xMax = 5.0;
const double CoordMapper::yMin = -0.5;
const double CoordMapper::yMax = 5.0;

/*!
 * wxEVT_PAINT event handler for ID_THE_FIELD_PANEL
 */

void ShotAnimationDialog::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(m_theField);

//	dc.SetAxisOrientation(true, true);

	CoordMapper m(dc.GetSize());
#define countof(x) sizeof(x)/sizeof(x[0])

	//dibujar el campo
	{
		dc.SetPen(*wxBLACK_PEN);
		wxPoint goalLine[] = { m.toDc(CoordMapper::xMin,0), m.toDc(CoordMapper::xMax,0) };
		wxPoint goalArea[] = { m.toDc(-2,0), m.toDc(-2,2), m.toDc(2,2), m.toDc(2,0) };
		wxPoint penaltyArea[] = { m.toDc(-3,0), m.toDc(-3,3), m.toDc(3,3), m.toDc(3,0) };
		wxPoint leftPost[] = { m.toDc(-1,-0.1), m.toDc(-1,0.1) };
		wxPoint rightPost[] = { m.toDc(1,-0.1), m.toDc(1,0.1) };
		dc.DrawLines(countof(goalLine), goalLine);
		dc.DrawLines(countof(goalArea), goalArea);
		dc.DrawLines(countof(penaltyArea), penaltyArea);
		dc.DrawLines(countof(leftPost), leftPost);
		dc.DrawLines(countof(rightPost), rightPost);
		dc.SetPen(wxNullPen);
	}

	//dibujar arquero
	{
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxCYAN_BRUSH);
		double x = m_currentStep < m_simulation.size() ? m_simulation[m_currentStep].keeperx : 0.0;
		wxPoint keeper0 = m.toDc(x-halfWidth, 0-halfWidth/3);
		wxPoint keeper1 = m.toDc(x+halfWidth, 0+halfWidth/3);
		dc.DrawRectangle(keeper0, wxSize(keeper1.x-keeper0.x+1, keeper1.y-keeper0.y+1));
		dc.SetPen(wxNullPen);
		dc.SetBrush(wxNullBrush);
	}

	double ballx = 0.0;
	double bally = 2.5;

	//dibujar trayectoria
	if (m_currentStep < m_simulation.size())
	{
		dc.SetPen(*wxMEDIUM_GREY_PEN);
		std::vector<wxPoint> trajectory;
		for (size_t i = 0; i <= m_currentStep; ++i) {
			if (m_simulation[i].ballx != std::numeric_limits<double>::infinity() && 
				m_simulation[i].bally != std::numeric_limits<double>::infinity()) 
			{
				ballx = m_simulation[i].ballx;
				bally = m_simulation[i].bally;
				trajectory.push_back(m.toDc(ballx, bally));
				dc.DrawCircle(trajectory.back(),1);
			}
		}
		if (!trajectory.empty()) {
			dc.DrawLines(trajectory.size(), &trajectory[0]);
			dc.SetPen(wxNullPen);
		}
	}

	//dibujar pelota
	{
		dc.SetPen(*wxBLACK_PEN);
		//dc.SetBrush(*wxCYAN_BRUSH);
		//dc.SetBrush(*wxWHITE_BRUSH);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		double x = ballx;
		double y = bally;
		wxPoint ball = m.toDc(x,y);
		wxCoord radius = (m.toDc(0.05,0)-m.toDc(0,0)).x; //desprolijo!
		radius = (std::max)(radius, 2);
		dc.DrawCircle(ball, radius);
		dc.SetPen(wxNullPen);
		dc.SetBrush(wxNullBrush);
	}



	//event.Skip();
}


/*!
 * wxEVT_SIZE event handler for ID_THE_FIELD_PANEL
 */

void ShotAnimationDialog::OnSize( wxSizeEvent& event )
{
	m_theField->Refresh();
////@begin wxEVT_SIZE event handler for ID_THE_FIELD_PANEL in ShotAnimationDialog.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_SIZE event handler for ID_THE_FIELD_PANEL in ShotAnimationDialog. 
}

void ShotAnimationDialog::OnTimer(wxTimerEvent& event)
{
	if (m_currentStep+1 < m_simulation.size())
	{
		++m_currentStep;
		m_theField->Refresh();
	}
	else
		m_timer.Stop();
}

void ShotAnimationDialog::setSimulation(const std::vector<SimulationStep> & simulation)
{
	m_simulation = simulation;
	m_currentStep = 0;
	bool ok = m_timer.Start(200,wxTIMER_CONTINUOUS);
	assert(ok);
}
