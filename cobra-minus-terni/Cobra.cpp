#include "Cobra.h"
#include "MainMenu.h"

#include <wx/wx.h>

#include <wx/image.h>     // For wxImage and handlers
#include <wx/bitmap.h>    // For wxBitmap
#include <wx/statbmp.h>   // For wxStaticBitmap control

wxIMPLEMENT_APP(Cobra);

bool Cobra::OnInit()
{
	wxInitAllImageHandlers();

	const wxString &MAIN_MENU_TITLE = "Cobra 0B.5";

	const int MAIN_MENU_WIDTH = 1080;
	const int MAIN_MENU_HEIGHT = 720;

	MainMenu* mainMenu = new MainMenu(MAIN_MENU_TITLE);

	mainMenu->SetClientSize(MAIN_MENU_WIDTH, MAIN_MENU_HEIGHT);
	mainMenu->Center();

	mainMenu->Show();

	return true;
}