#pragma once

#include <wx/string.h>
#include <wx/clntdata.h>

class IDEFileTreeData :
    public wxClientData
{
    public:
        IDEFileTreeData(const wxString& path) : m_path(path), m_isPopulated(false) {}
        const wxString& GetPath() const { return m_path; }

        // Optional: Flag to track if node's children have been populated
        // Useful for lazy loading, although this example repopulates on events
        bool IsPopulated() const { return m_isPopulated; }
        void SetPopulated(bool populated = true) { m_isPopulated = populated; }

    private:
        wxString m_path;
        bool m_isPopulated; // Flag if children added
};

