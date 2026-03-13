#pragma once
#include <wx/wx.h>

#include <wx/image.h>     // For wxImage and handlers
#include <wx/bitmap.h>    // For wxBitmap
#include <wx/statbmp.h>   // For wxStaticBitmap control

class IDEFrame;

class MainMenu : public wxFrame
{
	public:
		MainMenu(const wxString& title);

		wxString pathWhereProjectWillBeCreated;
		wxString pathWhereProjectWillBeOpened;

		wxString projectPath;
		wxString projectName;

	private:
		void getFolderForNewProject(wxCommandEvent &commmandEvent);
		void getNameOfNewProject();
		void createNewProject(wxString projectName);

		static bool startsWith(const std::string& str, const std::string& prefix);
		void applySettings(IDEFrame* p_ideFrame);
		
		void getExistingProjectFolder(wxCommandEvent &commandEvent);
		void openProject(wxString p_projectPath);

		wxDECLARE_EVENT_TABLE();
};
