#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"
#include "CommonHeaderWindow.h"
#include "InternalUseAreaWindow.h"
#include "BoardInfoWindow.h"
#include "ChassisInfoAreaWindow.h"
#include "ProductInfoWindow.h"
#include "MultiRecordWindow.h"

class InfoArea : public wxPanel
{
public:
    InfoArea(wxWindow * parent, wxWindowID id);
    ~InfoArea();
    bool SetInfo(FD::Unit * unit);
    FD::Unit * GetInfo(void);
    bool SaveInfo();

private:
    FD::Unit * m_unit;
    CommonHeaderWindow * m_commonHeader;
    InternalUseAreaWindow * m_internalUseArea;
    BoardInfoWindow * m_boardInfo;
    ChassisInfoAreaWindow * m_chassisInfo;
    ProductInfoWindow * m_productInfo;
    MultiRecordWindow * m_multiRecordArea;
};
