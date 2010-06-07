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
#include "AppModel.h"
#include "GoalkeeperBase.h"
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/config.h>
#include <cassert>
#include <fstream>
#include <cmath>
#include <limits>

#define metafor(iter,container) \
	for ((iter) = (container).begin(); (iter) != (container).end(); ++(iter))

const wxString goalkeepersCfgPath = wxT("/Goalkeepers");
const wxString testfilesCfgPath = wxT("/Testfiles");

void add(std::set<wxString> & where, const wxString & cfgPath, const wxArrayString & paths)
{
	wxConfigBase * cfg = wxConfig::Get();
	wxString prevCfgPath = cfg->GetPath();
	cfg->SetPath(cfgPath);

	wxArrayString::const_iterator it;
	metafor(it, paths)
		if (where.insert(*it).second)
			cfg->Write(wxString() << where.size(), *it);

	cfg->SetPath(prevCfgPath);
}

void del(std::set<wxString> & where, const wxString & cfgPath, const wxArrayString & paths)
{
	{
		wxArrayString::const_iterator it;
		metafor(it, paths)
			where.erase(*it);
	}

	{
		wxConfigBase * cfg = wxConfig::Get();
		wxString prevCfgPath = cfg->GetPath();
		cfg->DeleteGroup(cfgPath); //borro todo
		cfg->SetPath(cfgPath); //y lo regenero
		std::set<wxString>::iterator it; size_t i = 0;
		metafor(it, where)
			cfg->Write(wxString() << ++i, *it);
		cfg->SetPath(prevCfgPath);
	}
}

void get(std::set<wxString> & where, wxArrayString & paths)
{
	paths.clear();
	std::set<wxString>::const_iterator it;
	for (it = where.begin(); it != where.end(); ++it)
		paths.push_back(*it);
}

void load(std::set<wxString> & where, const wxString & cfgPath)
{
	wxConfigBase * cfg = wxConfig::Get();
	wxString prevCfgPath = cfg->GetPath();
	cfg->SetPath(cfgPath);
	wxString entry;
	long cookie;
	bool iterate = cfg->GetFirstEntry(entry, cookie);
	while (iterate) {
		wxString value;
		if (cfg->Read(entry, &value))
			where.insert(value);
		iterate = cfg->GetNextEntry(entry, cookie);
	}
	cfg->SetPath(prevCfgPath);
}

AppModel::AppModel()
{
	load(m_goalkeepers, goalkeepersCfgPath);
	load(m_testfiles, testfilesCfgPath);
}

void AppModel::addGoalkeepers(const wxArrayString & paths)
{
	add(m_goalkeepers, goalkeepersCfgPath, paths);
}

void AppModel::deleteGoalkeepers(const wxArrayString & paths)
{
	del(m_goalkeepers, goalkeepersCfgPath, paths);
}

void AppModel::getGoalkeepers(wxArrayString & paths)
{
	get(m_goalkeepers, paths);
}

void AppModel::addTestfiles(const wxArrayString & paths)
{
	add(m_testfiles, testfilesCfgPath, paths);
}

void AppModel::deleteTestfiles(const wxArrayString & paths)
{
	del(m_testfiles, testfilesCfgPath, paths);
}

void AppModel::getTestfiles(wxArrayString & paths)
{
	get(m_testfiles, paths);
}



bool AppModel::canRunTests() const
{
	return !m_goalkeepers.empty() && !m_testfiles.empty();
}

/// \todo FIXME Esto es portable??
wxString quote(const wxString & filename)
{
	return wxT("\"") + filename + wxT("\"");
}


void AppModel::runTests(ITestGUI & gui)
{
	assert(canRunTests());	
	gui.testingStarts();

	std::set<wxString>::const_iterator ikeeper;
	std::set<wxString>::const_iterator itest;

	metafor(ikeeper, m_goalkeepers) 
	{
		wxFileName keeper(*ikeeper);
		assert(keeper.IsOk() && keeper.IsFileExecutable());
		wxString keeperName = keeper.GetName();
		gui.setGoalkeeperName(keeperName);

		metafor(itest, m_testfiles) 
		{
			wxFileName test(*itest);
			assert(test.IsOk() && test.IsFileReadable());
			wxString testName = test.GetName();
			gui.setTestName(testName);

			wxString outputName = keeperName + testName;
			wxFileName output(test.GetPath(), outputName, wxT("txt"));

			wxString cmd = keeper.GetFullPath();
			cmd += wxT(" ");
			cmd += quote(test.GetFullPath());
			cmd += wxT(" ");
			cmd += quote(output.GetFullPath());

			gui.goalkeeperStarts();
			long retcode = wxExecute(cmd, wxEXEC_SYNC);
			gui.goalkeeperEnded();

			if (retcode == -1) {
				gui.reportTestFailure(_("No se pudo correr el programa arquero (aparentemente)."));
				continue;
			}

			analizeResults(gui, test.GetFullPath(), output.GetFullPath());
		}
	}

	gui.testingEnded();
}


void AppModel::analizeResults(ITestGUI & gui, const wxString & testFilename, const wxString & outputFilename)
{
	std::ifstream test(testFilename.mb_str()); // FIXME: conversión porque STL no soporta wchar_t :(
	if (!test) {
		gui.reportTestFailure(_("No se pudo abrir el archivo de test."));
		return;
	}

	std::ifstream output(outputFilename.mb_str());  // FIXME: conversión porque STL no soporta wchar_t :(
	if (!test) {
		gui.reportTestFailure(_("No se pudo abrir el archivo con la salida del arquero."));
		return;
	}

	GoalkeeperBase gk;
	std::vector<SimulationStep> steps;

	int nextMeassurement = 1;
	int meassurement; 
	while ((test >> meassurement) && meassurement != -1) 
	{
		if (meassurement < nextMeassurement) {
			gui.reportTestFailure(_("Parece haber un problema con el archivo de test."));
			return;
		}

		for (; nextMeassurement <= meassurement; ++nextMeassurement)
		{
			SimulationStep step;
			step.meassurement = nextMeassurement;

			int keeperResponse = -1;
			output >> keeperResponse;
			if (keeperResponse != nextMeassurement) {
				gui.reportTestFailure(_("El arquero reporta una respuesta no correspondiente a una medicion, o fallo la lectura."));
				return;
			}
			Movement move = invalid;
			output >> move;
			if (move == invalid) {
				gui.reportTestFailure(_("El arquero reporta una decision invalida."));
				return;
			}

			gk.update(move);
			step.ballx = std::numeric_limits<double>::infinity();
			step.bally = std::numeric_limits<double>::infinity();
			step.keeperx = gk.position();

			steps.push_back(step);
		}
		
		test >> steps.back().ballx >> steps.back().bally;
	}

	if (steps.empty()) {
		gui.reportTestFailure(_("No hay mediciones, o fallo la lectura."));
		return;
	}

	SimulationStep & last = steps.back();
	bool goal = 
		last.bally <= 0.0 && 
		leftPost < last.ballx && last.ballx < rightPost && //si es palo no es gol!
		fabs(last.keeperx - last.ballx) > halfWidth;

	gui.reportSimulation(goal, steps);
}
