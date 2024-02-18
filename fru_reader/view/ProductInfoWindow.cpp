#pragma once
#include "ProductInfoWindow.h"

ProductInfoWindow::ProductInfoWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Product Info")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxScrolledWindow * container = new wxScrolledWindow(this, wxID_ANY);
    wxFlexGridSizer * containerSizer = new wxFlexGridSizer(2, wxSize(10, 5));
    
    wxStaticText * formatVersion = new wxStaticText(container, wxID_ANY, "Format Version");
    wxStaticText * languadeCode = new wxStaticText(container, wxID_ANY, "languadeCode");
    wxStaticText * manufacturerName = new wxStaticText(container, wxID_ANY, "manufacturerName");
    wxStaticText * name = new wxStaticText(container, wxID_ANY, "name");
    wxStaticText * partNumber = new wxStaticText(container, wxID_ANY, "partNumber");
    wxStaticText * version = new wxStaticText(container, wxID_ANY, "version");
    wxStaticText * serialNumber = new wxStaticText(container, wxID_ANY, "serialNumber");
    wxStaticText * checksum = new wxStaticText(container, wxID_ANY, "checksum");

    m_formatVersionTxt = new wxTextCtrl(container, wxID_ANY, "Format Version");
    m_languadeCodeTxt = new wxTextCtrl(container, wxID_ANY, "languadeCode");
    m_manufacturerNameTxt = new wxTextCtrl(container, wxID_ANY, "manufacturerName");
    m_nameTxt = new wxTextCtrl(container, wxID_ANY, "name");
    m_partNumberTxt = new wxTextCtrl(container, wxID_ANY, "partNumber");
    m_versionTxt = new wxTextCtrl(container, wxID_ANY, "version");
    m_serialNumberTxt = new wxTextCtrl(container, wxID_ANY, "serialNumber");
    m_checksumTxt = new wxTextCtrl(container, wxID_ANY, "checksum");

    m_formatVersionTxt->Disable();
    m_languadeCodeTxt->Disable();
    m_checksumTxt->Disable();

    containerSizer->Add(formatVersion, wxSizerFlags(1));
    containerSizer->Add(m_formatVersionTxt, wxSizerFlags(1));
    containerSizer->Add(languadeCode, wxSizerFlags(1));
    containerSizer->Add(m_languadeCodeTxt, wxSizerFlags(1));
    containerSizer->Add(manufacturerName, wxSizerFlags(1));
    containerSizer->Add(m_manufacturerNameTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(name, wxSizerFlags(1));
    containerSizer->Add(m_nameTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(partNumber, wxSizerFlags(1));
    containerSizer->Add(m_partNumberTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(version, wxSizerFlags(1));
    containerSizer->Add(m_versionTxt, wxSizerFlags(1));
    containerSizer->Add(serialNumber, wxSizerFlags(1));
    containerSizer->Add(m_serialNumberTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
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

ProductInfoWindow::~ProductInfoWindow()
{
}

bool ProductInfoWindow::SetInfo(FD::ProductInfoArea * unit)
{
    m_product = unit;

    if (m_product != nullptr)
    {
        m_formatVersionTxt->SetValue(wxString(std::to_string(unit->formatVersion)));
        
        m_languadeCodeTxt->SetValue("English");
        
        m_manufacturerNameTxt->SetValue(wxString(unit->manufacturerName.data(), unit->manufacturerName.size()));
        m_manufacturerNameTxt->Enable();
        
        m_nameTxt->SetValue(wxString(unit->productName.data(), unit->productName.size()));
        m_nameTxt->Enable();
        
        m_serialNumberTxt->SetValue(wxString(unit->serialNumber.data(), unit->serialNumber.size()));
        m_serialNumberTxt->Enable();
        
        m_partNumberTxt->SetValue(wxString(unit->partNumber.data(), unit->partNumber.size()));
        m_partNumberTxt->Enable();

        m_versionTxt->SetValue(wxString(unit->productVersion.data(), unit->productVersion.size()));
        m_versionTxt->Enable();
        
        m_checksumTxt->SetValue(wxString(std::to_string(unit->checksum)));
    }
    else
    {
        m_formatVersionTxt->Clear();
        
        m_languadeCodeTxt->Clear();
        
        m_manufacturerNameTxt->Clear();
        m_manufacturerNameTxt->Disable();
        
        m_nameTxt->Clear();
        m_nameTxt->Disable();
        
        m_serialNumberTxt->Clear();
        m_serialNumberTxt->Disable();
        
        m_partNumberTxt->Clear();
        m_partNumberTxt->Disable();

        m_versionTxt->Clear();
        m_versionTxt->Disable();
        
        m_checksumTxt->Clear();
    }

    return true;
}