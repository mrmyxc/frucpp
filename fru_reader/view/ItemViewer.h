#pragma once
#include "wx/wx.h"
#include "InfoArea.h"

class ItemViewer : public wxPanel
{
public:
    ItemViewer(wxWindow * parent, wxWindowID id, InfoArea * area, std::vector<FD::Unit> * units);
    ~ItemViewer();

private:
    InfoArea * m_infoArea;
    std::vector<FD::Unit> * m_units;
    wxButton * m_addButton;
    wxButton * m_removeButton;
    wxButton * m_saveButton;

    void OnItemSelected(wxCommandEvent & event);
    void OnSaveButtonClicked(wxCommandEvent & event);
};

