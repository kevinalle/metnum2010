#ifndef _AppModel_H
#define _AppModel_H
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

#include <wx/string.h>
#include <wx/arrstr.h>
#include <set>
#include <vector>

struct SimulationStep
{
	int meassurement;
	double ballx, bally;
	double keeperx;
};

class ITestGUI
{
public:
	virtual void testingStarts() = 0;
	virtual void testingEnded() = 0;
	virtual void setGoalkeeperName(const wxString & name) = 0;
	virtual void setTestName(const wxString & name) = 0;
	virtual void goalkeeperStarts() = 0;
	virtual void goalkeeperEnded() = 0;
	virtual void reportTestFailure(const wxString & message) = 0;
	virtual void reportSimulation(bool isGoal, const std::vector<SimulationStep> & simulation) = 0;
};

class AppModel
{
public:
	AppModel();
public:
	void addGoalkeepers(const wxArrayString & paths);
	void deleteGoalkeepers(const wxArrayString & paths);
	void getGoalkeepers(wxArrayString & paths);
	void addTestfiles(const wxArrayString & paths);
	void deleteTestfiles(const wxArrayString & paths);
	void getTestfiles(wxArrayString & paths);
	bool canRunTests() const;
	void runTests(ITestGUI & gui);
private:
	void analizeResults(ITestGUI & gui, const wxString & testFilename, const wxString & outputFilename);
private:
	std::set<wxString> m_goalkeepers;
	std::set<wxString> m_testfiles;
};

#endif