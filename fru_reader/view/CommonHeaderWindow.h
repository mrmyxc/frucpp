#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class CommonHeaderWindow : public wxStaticBox
{
public:
    CommonHeaderWindow(wxWindow * parent, wxWindowID id);
    ~CommonHeaderWindow();
    bool SetInfo(FD::CommonHeader * unit);

private:
    FD::CommonHeader * m_header;
    wxTextCtrl * m_formatVersionTxt;
    wxTextCtrl * m_iaOffsetTxt;
    wxTextCtrl * m_ciaOffsetTxt;
    wxTextCtrl * m_baOffsetTxt;
    wxTextCtrl * m_piOffsetTxt;
    wxTextCtrl * m_checksumTxt;
};
