#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class BoardInfoWindow : public wxStaticBox
{
public:
    BoardInfoWindow(wxWindow * parent, wxWindowID id);
    ~BoardInfoWindow();
    bool SetInfo(FD::BoardArea * boardInfo);
    bool SaveInfo();

private:
    FD::BoardArea * m_board;
    wxTextCtrl * m_formatVersionTxt;
    wxTextCtrl * m_languadeCodeTxt;
    wxTextCtrl * m_manufacturerDateTimeTxt;
    wxTextCtrl * m_manufacturerNameTxt;
    wxTextCtrl * m_nameTxt;
    wxTextCtrl * m_serialNumberTxt;
    wxTextCtrl * m_partNumberTxt;
    wxTextCtrl * m_checksumTxt;
};
