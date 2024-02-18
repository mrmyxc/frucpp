#pragma once
#include "ChassisInfoAreaWindow.h"

ChassisInfoAreaWindow::ChassisInfoAreaWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Chassis Info")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxScrolledWindow * container = new wxScrolledWindow(this, wxID_ANY);
    wxFlexGridSizer * containerSizer = new wxFlexGridSizer(2, wxSize(10, 5));
    
    wxStaticText * formatVersion = new wxStaticText(container, wxID_ANY, "Format Version");
    wxStaticText * chassisType = new wxStaticText(container, wxID_ANY, "chassisType");
    wxStaticText * partNumber = new wxStaticText(container, wxID_ANY, "partNumber");
    wxStaticText * serialNumber = new wxStaticText(container, wxID_ANY, "serialNumber");
    wxStaticText * checksum = new wxStaticText(container, wxID_ANY, "checksum");

    m_formatVersionTxt = new wxTextCtrl(container, wxID_ANY, "Format Version");
    m_chassisTypeTxt = new wxTextCtrl(container, wxID_ANY, "chassisType");
    m_serialNumberTxt = new wxTextCtrl(container, wxID_ANY, "serialNumber");
    m_partNumberTxt = new wxTextCtrl(container, wxID_ANY, "partNumber");
    m_checksumTxt = new wxTextCtrl(container, wxID_ANY, "checksum");

    m_formatVersionTxt->Disable();
    m_checksumTxt->Disable();

    containerSizer->Add(formatVersion, wxSizerFlags(1));
    containerSizer->Add(m_formatVersionTxt, wxSizerFlags(1));
    containerSizer->Add(chassisType, wxSizerFlags(1));
    containerSizer->Add(m_chassisTypeTxt, wxSizerFlags(1));
    containerSizer->Add(partNumber, wxSizerFlags(1));
    containerSizer->Add(m_partNumberTxt, wxSizerFlags(1));
    containerSizer->Add(serialNumber, wxSizerFlags(1));
    containerSizer->Add(m_serialNumberTxt, wxSizerFlags(1));
    containerSizer->Add(checksum, wxSizerFlags(1));
    containerSizer->Add(m_checksumTxt, wxSizerFlags(1));

    containerSizer->AddGrowableCol(1, 1);

    container->SetScrollbars(10, 10, 100, 100);
    container->SetSizer(containerSizer);
    container->FitInside();
    container->SetScrollRate(5, 5);

    mainSizer->Add(0, 0, wxSizerFlags(0).Border(wxLEFT, 10)); // Add dummy object to align texts
    mainSizer->Add(container, wxSizerFlags(1).Expand().Border(wxTOP, 15));
    this->SetSizer(mainSizer);

    SetInfo(nullptr);
}

ChassisInfoAreaWindow::~ChassisInfoAreaWindow()
{
}

bool ChassisInfoAreaWindow::SetInfo(FD::ChassisInfoArea * unit)
{
    m_chassisInfo = unit;

    if (m_chassisInfo != nullptr)
    {
        m_formatVersionTxt->ChangeValue(wxString(std::to_string(unit->formatVersion)));

        m_chassisTypeTxt->ChangeValue(wxString(std::to_string(unit->type)));
        m_chassisTypeTxt->Enable();
        
        m_serialNumberTxt->ChangeValue(wxString(unit->serialNumber.data(), unit->serialNumber.size()));
        m_serialNumberTxt->Enable();
        
        m_partNumberTxt->ChangeValue(wxString(unit->partNumber.data(), unit->partNumber.size()));
        m_partNumberTxt->Enable();
        
        m_checksumTxt->ChangeValue(wxString(std::to_string(unit->checksum)));
    }
    else
    {
        m_formatVersionTxt->ChangeValue("");

        m_chassisTypeTxt->ChangeValue("");
        m_chassisTypeTxt->Disable();
        
        m_serialNumberTxt->ChangeValue("");
        m_serialNumberTxt->Disable();
        
        m_partNumberTxt->ChangeValue("");
        m_partNumberTxt->Disable();
        
        m_checksumTxt->ChangeValue("");
        m_checksumTxt->Disable();
    }

    return true;
}
