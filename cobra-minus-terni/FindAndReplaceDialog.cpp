#include "FindAndReplaceDialog.h"

#include "CobraWidgetID.h"

wxBEGIN_EVENT_TABLE(FindAndReplaceDialog, wxDialog)
	EVT_BUTTON(FINDANDREPLACE_DIALOG_OK_ID, FindAndReplaceDialog::ok)
	EVT_BUTTON(FINDANDREPLACE_DIALOG_CLOSE_ID, FindAndReplaceDialog::close)
wxEND_EVENT_TABLE()

FindAndReplaceDialog::FindAndReplaceDialog() 
	: wxDialog(NULL, wxID_ANY, "Find", wxDefaultPosition, wxSize(250, 230))
{
	wxPanel* panel = new wxPanel(this);

	wxBoxSizer* verticalBoxLayout = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* horizontalBoxLayout = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBox* searchBox = new wxStaticBox(panel, wxID_ANY, wxT("Search"), wxPoint(5, 5), wxSize(175, (int) (75 * 0.75)));  // 56.25

	wxStaticText* findLabel = new wxStaticText(panel, wxID_ANY, "Find: ", wxPoint(15, 30), wxDefaultSize, wxALIGN_LEFT);
	searchTextBox = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(50, 25), wxDefaultSize);

	wxStaticBox* matchBox = new wxStaticBox(panel, wxID_ANY, wxT("Match"), wxPoint(5, 60), wxSize(175, 100));
	
	matchCase = new wxCheckBox(panel, wxID_ANY, "Match Case", wxPoint(15, 85), wxDefaultSize);
	matchWholeWord = new wxCheckBox(panel, wxID_ANY, "Match Whole Word", wxPoint(15, 110), wxDefaultSize);

	okButton = new wxButton(this, FINDANDREPLACE_DIALOG_OK_ID, wxT("Ok"),
		wxDefaultPosition, wxSize(70, 30));
	closeButton = new wxButton(this, FINDANDREPLACE_DIALOG_CLOSE_ID, wxT("Close"),
		wxDefaultPosition, wxSize(70, 30));

	horizontalBoxLayout->Add(okButton, 1);
	horizontalBoxLayout->Add(closeButton, 1, wxLEFT, 5);

	verticalBoxLayout->Add(panel, 1);
	verticalBoxLayout->Add(horizontalBoxLayout, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	SetSizer(verticalBoxLayout);

	Centre();
}

wxString FindAndReplaceDialog::getSearchText()
{
	return searchTextBox->GetValue();
}

bool FindAndReplaceDialog::hasMatchCase()
{
	return matchCase->IsChecked();
}

bool FindAndReplaceDialog::hasMatchWholeWord()
{
	return matchWholeWord->IsChecked();
}

void FindAndReplaceDialog::ok(wxCommandEvent& commandEvent)
{
	FindAndReplaceDialog::AcceptAndClose();
}

void FindAndReplaceDialog::close(wxCommandEvent& commandEvent)
{
	FindAndReplaceDialog::Close();
}
