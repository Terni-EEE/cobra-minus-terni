#pragma once
#include <wx/wx.h>

class FindAndReplaceDialog : public wxDialog
{
	public:
		FindAndReplaceDialog();

		wxString getSearchText();

		bool hasMatchCase();
		bool hasMatchWholeWord();
			
	private:
		wxTextCtrl* searchTextBox;

		wxCheckBox* matchCase;
		wxCheckBox* matchWholeWord;

		wxButton* okButton;
		wxButton* closeButton;

		void ok(wxCommandEvent &commandEvent);
		void close(wxCommandEvent& commandEvent);

		wxDECLARE_EVENT_TABLE();
};
