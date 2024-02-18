#pragma once
#include "InternalUseAreaWindow.h"

InternalUseAreaWindow::InternalUseAreaWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Internal Use Area")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxScrolledWindow * container = new wxScrolledWindow(this, wxID_ANY);
    wxFlexGridSizer * containerSizer = new wxFlexGridSizer(2, wxSize(10, 5));
    
    wxStaticText * formatVersion = new wxStaticText(container, wxID_ANY, "Format");
    m_formatVersionTxt = new wxTextCtrl(container, wxID_ANY, "Format");
    wxStaticText * iaOffset = new wxStaticText(container, wxID_ANY, "Internal Use Area");
    m_iaDataTxt = new wxTextCtrl(container, wxID_ANY, "Data");

    m_formatVersionTxt->Disable();
    m_iaDataTxt->Disable();

    m_formatVersionTxt->Clear();
    m_iaDataTxt->Clear();

    containerSizer->Add(formatVersion, wxSizerFlags(1));
    containerSizer->Add(m_formatVersionTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(iaOffset, wxSizerFlags(1));
    containerSizer->Add(m_iaDataTxt, wxSizerFlags(1).Expand());
    containerSizer->AddGrowableRow(1, 1);

    container->SetScrollbars(10, 10, 100, 100);
    container->SetSizer(containerSizer);
    container->FitInside();
    container->SetScrollRate(5, 5);

    mainSizer->Add(0, 0, wxSizerFlags(0).Border(wxLEFT, 10)); // Add dummy object to align texts
    mainSizer->Add(container, wxSizerFlags(1).Expand().Border(wxTOP, 15));
    this->SetSizer(mainSizer);

    SetInfo(nullptr);
}

InternalUseAreaWindow::~InternalUseAreaWindow()
{
}

bool InternalUseAreaWindow::SetInfo(FD::InternalUseArea * unit)
{
    m_internal = unit;
    return true;
}
