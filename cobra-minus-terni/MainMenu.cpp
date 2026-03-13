#include "MainMenu.h"
#include "IDEFrame.h"

#include "CobraWidgetID.h"

#include <windows.h>

#include <iostream>

#include <wx/image.h>     // For wxImage and handlers
#include <wx/bitmap.h>    // For wxBitmap
#include <wx/statbmp.h>   // For wxStaticBitmap control

#include <wx/wx.h>
#include <wx/stc/stc.h>

#include <wx/dir.h>
#include <wx/filename.h>

#include <wx/filedlg.h>
#include <wx/textdlg.h>

#include <fstream>
#include <string>

#include <regex>

#include "external/json.hpp"

using json = nlohmann::json;

wxBEGIN_EVENT_TABLE(MainMenu, wxFrame)
	EVT_BUTTON(CREATE_NEW_PROJECT_BUTTON_ID, MainMenu::getFolderForNewProject)
	EVT_BUTTON(OPEN_PROJECT_BUTTON_ID, MainMenu::getExistingProjectFolder)
wxEND_EVENT_TABLE()

void LogToOutputWindow(const std::string& message) 
{
	OutputDebugStringA(message.c_str());
}

MainMenu::MainMenu(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainMenuPanel = new wxPanel(this);

	SetBackgroundColour(wxColor(36, 33, 33));

	/*wxImage cobraFullImage;
	wxString cobraFullImagePath = wxT("assets\\images\\cobrafull.png");

	if (cobraFullImage.LoadFile(cobraFullImagePath))
	{
		wxBitmap cobraFullBitmap(cobraFullImage);
		wxStaticBitmap* cobraFullControl = new wxStaticBitmap(
			mainMenuPanel, wxID_ANY, cobraFullBitmap, wxPoint(70, 50)
		);
	}*/

	wxButton* createNewProjectButton = new wxButton(
        mainMenuPanel, CREATE_NEW_PROJECT_BUTTON_ID, "New Project", 
		wxPoint(70, 200), wxSize(125, 50)
    );

	wxButton* openNewProjectButton = new wxButton(
		mainMenuPanel, OPEN_PROJECT_BUTTON_ID, "Open Project", 
		wxPoint(250, 200), wxSize(125, 50)
	);

	CreateStatusBar();
}

void MainMenu::getFolderForNewProject(wxCommandEvent& commandEvent)
{
	wxLogStatus("CREATING NEW PROJECT.");

	wxDirDialog dialog(this, "Choose Directory for the Project", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (dialog.ShowModal() == wxID_OK)
	{
		pathWhereProjectWillBeCreated = dialog.GetPath();
		wxLogStatus("PROJECT WILL BE CREATED IN " + pathWhereProjectWillBeCreated);

		getNameOfNewProject();
	}
}

void MainMenu::getNameOfNewProject()
{
	projectName = wxGetTextFromUser("Enter your project name:", "Project Name");

	if (!projectName.IsEmpty())
	{
		wxLogStatus("PROJECT IS NAMED " + projectName);
		
		createNewProject(projectName);
	}
}

bool MainMenu::startsWith(const std::string& str, const std::string& prefix) 
{
	return str.substr(0, prefix.size()) == prefix;
}

void MainMenu::applySettings(IDEFrame* p_ideFrame)
{
	// Construct the correct settings file path
	wxString settingsPath = projectPath + wxFileName::GetPathSeparator() +
		".cobra" + wxFileName::GetPathSeparator() + "settings.json";

	std::ifstream settingsFile(settingsPath.ToStdString());
	json settings;

	if (settingsFile.is_open())
	{
		try
		{
			settingsFile >> settings; // Parse the JSON file
			settingsFile.close();
		}
		catch (const json::parse_error& e)
		{
			std::cerr << "JSON parse error: " << e.what() << std::endl;
			return;
		}
	}
	else
	{
		std::cerr << "Failed to open settings.json at " << settingsPath << std::endl;
		return;
	}

	// Apply theme with fallback to default if not specified
	std::string theme = "Cobra - Dark Theme"; // default value
	if (settings.contains("editor.theme"))
	{
		theme = settings["editor.theme"];
		LogToOutputWindow("editor.theme GOTTEN.");
	}

	LogToOutputWindow(theme);
	p_ideFrame->applyTheme(theme);

	// Apply font settings with fallback to defaults if not specified
	std::string fontFace = "Anonymous Pro"; // default value
	int fontSize = 13; // default value

	if (settings.contains("editor.fontFace"))
	{
		fontFace = settings["editor.fontFace"];
		LogToOutputWindow("editor.fontFace GOTTEN");
	}

	if (settings.contains("editor.fontSize"))
	{
		fontSize = settings["editor.fontSize"];
		LogToOutputWindow("editor.fontSize GOTTEN");
	}

	LogToOutputWindow(fontFace);
	LogToOutputWindow(std::to_string(fontSize));

	p_ideFrame->setStyleFont(fontFace, fontSize);
}

void MainMenu::createNewProject(wxString projectName)
{
	projectPath = pathWhereProjectWillBeCreated + "\\" + projectName;

	if (wxFileName::Mkdir(projectPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
	{
		wxLogStatus("PROJECT CREATED AS " + projectPath);
	}
	else
	{
		wxLogStatus("FAILURE TO CREATE PROJECT AS " + projectPath);
	}

	std::ofstream mainPythonFile(projectPath.ToStdString() + "\\main.py");

	if (mainPythonFile.is_open())
	{
		mainPythonFile.close();
		wxLogStatus("main.py FILE CREATED SUCCESSFULLY.");

		IDEFrame* ideFrame = new IDEFrame("Cobra - " + projectPath, projectPath);

		this->Show(false);
		ideFrame->Show(true);
	}
	else
	{
		wxLogStatus("main.py FILE FAILED TO CREATE.");
	}
}

void MainMenu::getExistingProjectFolder(wxCommandEvent& commandEvent)
{
	wxLogStatus("OPENING AN EXISTING PROJECT.");

	wxDirDialog dialog(this, "Choose Project Directory to Open", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (dialog.ShowModal() == wxID_OK)
	{
		pathWhereProjectWillBeOpened = dialog.GetPath();
		wxLogStatus("PROJECT " + pathWhereProjectWillBeOpened + " WILL BE OPENED.");

		openProject(pathWhereProjectWillBeOpened);
	}
}

void MainMenu::openProject(wxString p_projectPath)
{
	projectPath = p_projectPath;
	
	std::ifstream fileToOpen(projectPath.ToStdString() + "\\main.py");

	IDEFrame* ideFrame = new IDEFrame("Cobra - " + projectPath, projectPath);

	if (fileToOpen.is_open())
	{
		std::string textToOutputToFileToOpen;

		std::string line;
		while (std::getline(fileToOpen, line))
		{
			textToOutputToFileToOpen += line + "\n";
		}

		ideFrame->codeBody->ClearAll();
		ideFrame->codeBody->SetText(textToOutputToFileToOpen);

		applySettings(ideFrame);
	}
	else
	{
		ideFrame->codeBody->SetText("");
	}

	this->Show(false);
	ideFrame->Show(true);
}
