#pragma once
#include "CommonHeaderWindow.h"

CommonHeaderWindow::CommonHeaderWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Common Header")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxScrolledWindow * container = new wxScrolledWindow(this, wxID_ANY);
    wxFlexGridSizer * containerSizer = new wxFlexGridSizer(2, wxSize(10, 5));

    wxStaticText * formatVersion = new wxStaticText(container, wxID_ANY, "Format Version");
    m_formatVersionTxt = new wxTextCtrl(container, wxID_ANY, "Format Version");
    wxStaticText * iaOffset = new wxStaticText(container, wxID_ANY, "Internal Use Area");
    m_iaOffsetTxt = new wxTextCtrl(container, wxID_ANY, "Offset");
    wxStaticText * ciaOffset = new wxStaticText(container, wxID_ANY, "Chassis Info");
    m_ciaOffsetTxt = new wxTextCtrl(container, wxID_ANY, "Offset");
    wxStaticText * baOffset = new wxStaticText(container, wxID_ANY, "Board Area");
    m_baOffsetTxt = new wxTextCtrl(container, wxID_ANY, "Offset");
    wxStaticText * piOffset = new wxStaticText(container, wxID_ANY, "Product Info");
    m_piOffsetTxt = new wxTextCtrl(container, wxID_ANY, "Offset");
    wxStaticText * checksum = new wxStaticText(container, wxID_ANY, "Checksum");
    m_checksumTxt = new wxTextCtrl(container, wxID_ANY, "Checksum");

    m_formatVersionTxt->Disable();
    m_iaOffsetTxt->Disable();
    m_ciaOffsetTxt->Disable();
    m_baOffsetTxt->Disable();
    m_piOffsetTxt->Disable();
    m_checksumTxt->Disable();

    containerSizer->Add(formatVersion, wxSizerFlags(1));
    containerSizer->Add(m_formatVersionTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(iaOffset, wxSizerFlags(1));
    containerSizer->Add(m_iaOffsetTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(ciaOffset, wxSizerFlags(1));
    containerSizer->Add(m_ciaOffsetTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(baOffset, wxSizerFlags(1));
    containerSizer->Add(m_baOffsetTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(piOffset, wxSizerFlags(1));
    containerSizer->Add(m_piOffsetTxt, wxSizerFlags(1).Expand());
    containerSizer->Add(checksum, wxSizerFlags(1));
    containerSizer->Add(m_checksumTxt, wxSizerFlags(1).Expand());

    container->SetScrollbars(10, 10, 100, 100);
    container->SetSizer(containerSizer);
    container->FitInside();
    container->SetScrollRate(5, 5);

    mainSizer->Add(0, 0, wxSizerFlags(0).Border(wxLEFT, 10)); // Add dummy object to align texts
    mainSizer->Add(container, wxSizerFlags(1).Expand().Border(wxTOP, 15));
    this->SetSizer(mainSizer);

    SetInfo(nullptr);
}

CommonHeaderWindow::~CommonHeaderWindow()
{
}

bool CommonHeaderWindow::SetInfo(FD::CommonHeader * unit)
{
    m_header = unit;
    
    if (unit != nullptr)
    {
        m_formatVersionTxt->SetValue(wxString(std::to_string(unit->formatVersion)));
        m_iaOffsetTxt->SetValue(wxString(std::to_string(unit->internalUse)));
        m_ciaOffsetTxt->SetValue(wxString(std::to_string(unit->chassisInfo)));
        m_baOffsetTxt->SetValue(wxString(std::to_string(unit->boardArea)));
        m_piOffsetTxt->SetValue(wxString(std::to_string(unit->productInfoArea)));
        m_checksumTxt->SetValue(wxString(std::to_string(unit->checksum)));
    }
    else
    {
        m_formatVersionTxt->Clear();
        m_iaOffsetTxt->Clear();
        m_ciaOffsetTxt->Clear();
        m_baOffsetTxt->Clear();
        m_piOffsetTxt->Clear();
        m_checksumTxt->Clear();
    }

    return true;
}

