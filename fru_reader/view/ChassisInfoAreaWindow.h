#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class ChassisInfoAreaWindow : public wxStaticBox
{
public:
    ChassisInfoAreaWindow(wxWindow * parent, wxWindowID id);
    ~ChassisInfoAreaWindow();
    bool SetInfo(FD::ChassisInfoArea * unit);

private:
    FD::ChassisInfoArea * m_chassisInfo;
    wxTextCtrl * m_formatVersionTxt;
    wxTextCtrl * m_chassisTypeTxt;
    wxTextCtrl * m_serialNumberTxt;
    wxTextCtrl * m_partNumberTxt;
    wxTextCtrl * m_checksumTxt;
};
