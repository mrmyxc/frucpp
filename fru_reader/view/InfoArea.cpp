#pragma once
#include "InfoArea.h"
#include "CommonHeaderWindow.h"
#include "InternalUseAreaWindow.h"
#include "BoardInfoWindow.h"
#include "ChassisInfoAreaWindow.h"
#include "ProductInfoWindow.h"
#include "MultiRecordWindow.h"
#include "../model/Unit.h"

InfoArea::InfoArea(wxWindow * parent, wxWindowID id) : wxPanel(parent, id)
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer * level1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer * level2Sizer = new wxBoxSizer(wxHORIZONTAL);

    m_commonHeader = new CommonHeaderWindow(this, wxID_ANY), wxSizerFlags(1).Border(wxALL, 5).Expand();
    m_internalUseArea = new InternalUseAreaWindow(this, wxID_ANY), wxSizerFlags(1).Border(wxALL, 5).Expand();
    m_chassisInfo = new ChassisInfoAreaWindow(this, wxID_ANY), wxSizerFlags(1).Border(wxALL, 5).Expand();

    m_boardInfo = new BoardInfoWindow(this, wxID_ANY), wxSizerFlags(1).Expand();
    m_productInfo = new ProductInfoWindow(this, wxID_ANY), wxSizerFlags(1).Expand();

    m_multiRecordArea = new MultiRecordWindow(this, wxID_ANY), wxSizerFlags(1).Expand();

    level1Sizer->Add(m_commonHeader, wxSizerFlags(1).Expand());
    level1Sizer->Add(m_internalUseArea, wxSizerFlags(1).Expand());
    level1Sizer->Add(m_chassisInfo, wxSizerFlags(1).Expand());
    mainSizer->Add(level1Sizer, wxSizerFlags(1).Expand());
    level2Sizer->Add(m_boardInfo, wxSizerFlags(1).Expand());
    level2Sizer->Add(m_productInfo, wxSizerFlags(1).Expand());
    mainSizer->Add(level2Sizer, wxSizerFlags(2).Expand());
    mainSizer->Add(m_multiRecordArea, wxSizerFlags(1).Expand());
    
    this->SetSizerAndFit(mainSizer);

    SetInfo(nullptr);
}

InfoArea::~InfoArea()
{
}

bool InfoArea::SetInfo(FD::Unit * unit)
{
    m_unit = unit;

    if (unit != nullptr)
    {
        m_commonHeader->SetInfo(&unit->header);
        m_internalUseArea->SetInfo(&unit->internalUseArea);
        m_chassisInfo->SetInfo(&unit->chassisInfoArea);
        m_boardInfo->SetInfo(&unit->boardArea);
        m_productInfo->SetInfo(&unit->productInfoArea);
        m_multiRecordArea->SetInfo(&unit->multiRecordArea);
    }
    else
    {
        m_commonHeader->SetInfo(nullptr);
        m_internalUseArea->SetInfo(nullptr);
        m_chassisInfo->SetInfo(nullptr);
        m_boardInfo->SetInfo(nullptr);
        m_productInfo->SetInfo(nullptr);
        m_multiRecordArea->SetInfo(nullptr);
    }

    return false;
}

FD::Unit * InfoArea::GetInfo(void)
{
    return m_unit;
}

bool InfoArea::SaveInfo()
{
    if (m_unit == nullptr) 
    {
        return false;
    }

    m_boardInfo->SaveInfo();

    return true;
}
