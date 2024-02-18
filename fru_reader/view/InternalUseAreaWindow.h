#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class InternalUseAreaWindow : public wxStaticBox
{
public:
    InternalUseAreaWindow(wxWindow * parent, wxWindowID id);
    ~InternalUseAreaWindow();
    bool SetInfo(FD::InternalUseArea * unit);

private:
    FD::InternalUseArea * m_internal;
    wxTextCtrl * m_formatVersionTxt;
    wxTextCtrl * m_iaDataTxt;
};
