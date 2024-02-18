#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class ProductInfoWindow : public wxStaticBox
{
public:
    ProductInfoWindow(wxWindow * parent, wxWindowID id);
    ~ProductInfoWindow();
    bool SetInfo(FD::ProductInfoArea * unit);

private:
    FD::ProductInfoArea * m_product;
    wxTextCtrl * m_formatVersionTxt;
    wxTextCtrl * m_languadeCodeTxt;
    wxTextCtrl * m_manufacturerNameTxt;
    wxTextCtrl * m_nameTxt;
    wxTextCtrl * m_partNumberTxt;
    wxTextCtrl * m_versionTxt;
    wxTextCtrl * m_serialNumberTxt;
    wxTextCtrl * m_checksumTxt;
};
