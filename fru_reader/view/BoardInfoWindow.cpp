#pragma once
#include "BoardInfoWindow.h"
#include <time.h>

constexpr time_t EPOCH_OFFSET = 820454400;

BoardInfoWindow::BoardInfoWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Board Info")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxScrolledWindow * container = new wxScrolledWindow(this, wxID_ANY);
    wxFlexGridSizer * containerSizer = new wxFlexGridSizer(2, wxSize(10, 5));
    
    wxStaticText * formatVersion = new wxStaticText(container, wxID_ANY, "Format Version");
    wxStaticText * languadeCode = new wxStaticText(container, wxID_ANY, "languadeCode");
    wxStaticText * manufacturerDateTime = new wxStaticText(container, wxID_ANY, "manufacturerDateTime");
    wxStaticText * manufacturerName = new wxStaticText(container, wxID_ANY, "manufacturerName");
    wxStaticText * name = new wxStaticText(container, wxID_ANY, "name");
    wxStaticText * serialNumber = new wxStaticText(container, wxID_ANY, "serialNumber");
    wxStaticText * partNumber = new wxStaticText(container, wxID_ANY, "partNumber");
    wxStaticText * checksum = new wxStaticText(container, wxID_ANY, "checksum");

    m_formatVersionTxt = new wxTextCtrl(container, wxID_ANY, "Format Version");
    m_languadeCodeTxt = new wxTextCtrl(container, wxID_ANY, "languadeCode");
    m_manufacturerDateTimeTxt = new wxTextCtrl(container, wxID_ANY, "manufacturerDateTime");
    m_manufacturerNameTxt = new wxTextCtrl(container, wxID_ANY, "manufacturerName");
    // m_manufacturerNameTxt->Bind(wxEVT_TEXT, &BoardInfoWindow::OnTextChanged, this);
    m_nameTxt = new wxTextCtrl(container, wxID_ANY, "name");
    // m_nameTxt->Bind(wxEVT_TEXT, &BoardInfoWindow::OnTextChanged, this);
    m_serialNumberTxt = new wxTextCtrl(container, wxID_ANY, "serialNumber");
    // m_serialNumberTxt->Bind(wxEVT_TEXT, &BoardInfoWindow::OnTextChanged, this);
    m_partNumberTxt = new wxTextCtrl(container, wxID_ANY, "partNumber");
    // m_partNumberTxt->Bind(wxEVT_TEXT, &BoardInfoWindow::OnTextChanged, this);
    m_checksumTxt = new wxTextCtrl(container, wxID_ANY, "checksum");

    containerSizer->Add(formatVersion, wxSizerFlags(1));
    containerSizer->Add(m_formatVersionTxt, wxSizerFlags(1));
    containerSizer->Add(languadeCode, wxSizerFlags(1));
    containerSizer->Add(m_languadeCodeTxt, wxSizerFlags(1));
    containerSizer->Add(manufacturerDateTime, wxSizerFlags(1));
    containerSizer->Add(m_manufacturerDateTimeTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(manufacturerName, wxSizerFlags(1));
    containerSizer->Add(m_manufacturerNameTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(name, wxSizerFlags(1));
    containerSizer->Add(m_nameTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(serialNumber, wxSizerFlags(1));
    containerSizer->Add(m_serialNumberTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(partNumber, wxSizerFlags(1));
    containerSizer->Add(m_partNumberTxt, wxSizerFlags(1).Expand().Border(wxRIGHT, 5));
    containerSizer->Add(checksum, wxSizerFlags(1));
    containerSizer->Add(m_checksumTxt, wxSizerFlags(1));

    containerSizer->AddGrowableCol(1, 1);

    m_manufacturerDateTimeTxt->Disable();
    m_checksumTxt->Disable();
    m_languadeCodeTxt->Disable();

    container->SetScrollbars(10, 10, 100, 100);
    container->SetSizer(containerSizer);
    container->FitInside();
    container->SetScrollRate(5, 5);

    mainSizer->Add(0, 0, wxSizerFlags(0).Border(wxLEFT, 10)); // Add dummy object to align texts
    mainSizer->Add(container, wxSizerFlags(1).Expand().Border(wxTOP, 15));
    this->SetSizer(mainSizer);

    SetInfo(nullptr);
}

BoardInfoWindow::~BoardInfoWindow()
{
}

bool BoardInfoWindow::SetInfo(FD::BoardArea * unit)
{
    m_board = unit;

    if (m_board != nullptr)
    {
        m_formatVersionTxt->ChangeValue(wxString(std::to_string(unit->formatVersion)));
        m_formatVersionTxt->Enable();
        
        m_languadeCodeTxt->ChangeValue("English");

        time_t time = unit->manufacturerDateTime[0] + unit->manufacturerDateTime[1] << 8U + unit->manufacturerDateTime[1] << 16U;
        time += EPOCH_OFFSET;
        
        m_manufacturerDateTimeTxt->ChangeValue(wxString(ctime(&time)));
        
        m_manufacturerNameTxt->ChangeValue(wxString(unit->manufacturerName.data(), unit->manufacturerName.size()));
        m_manufacturerNameTxt->Enable();
        
        m_nameTxt->ChangeValue(wxString(unit->productName.data(), unit->productName.size()));
        m_nameTxt->Enable();
        
        m_serialNumberTxt->ChangeValue(wxString(unit->serialNumber.data(), unit->serialNumber.size()));
        m_serialNumberTxt->Enable();
        
        m_partNumberTxt->ChangeValue(wxString(unit->partNumber.data(), unit->partNumber.size()));
        m_partNumberTxt->Enable();
        
        m_checksumTxt->ChangeValue(wxString(std::to_string(unit->checksum)));
    }
    else
    {
        m_formatVersionTxt->ChangeValue("");
        m_formatVersionTxt->Disable();
        
        m_languadeCodeTxt->ChangeValue("");
        m_languadeCodeTxt->Disable();
        
        m_manufacturerDateTimeTxt->ChangeValue("");
        
        m_manufacturerNameTxt->ChangeValue("");
        m_manufacturerNameTxt->Disable();
        
        m_nameTxt->ChangeValue("");
        m_nameTxt->Disable();
        
        m_serialNumberTxt->ChangeValue("");
        m_serialNumberTxt->Disable();
        
        m_partNumberTxt->ChangeValue("");
        m_partNumberTxt->Disable();
        
        m_checksumTxt->ChangeValue("");
        m_checksumTxt->Disable();
    }

    return true;
}

bool BoardInfoWindow::SaveInfo()
{
    if (m_board == nullptr)
    {
        return false;
    }

    wxString currentString;

    currentString = m_manufacturerNameTxt->GetValue();
    m_board->manufacturerName.clear();
    m_board->manufacturerNameTL = 0x00 | currentString.length();
    std::copy(currentString.begin(), currentString.end(), std::back_inserter(m_board->manufacturerName));
    
    currentString = m_nameTxt->GetValue();
    m_board->productName.clear();
    m_board->productNameTL = 0x00 | currentString.length();
    std::copy(currentString.begin(), currentString.end(), std::back_inserter(m_board->productName));

    currentString = m_partNumberTxt->GetValue();
    m_board->partNumber.clear();
    m_board->partNumberTL = 0x00 | currentString.length();
    std::copy(currentString.begin(), currentString.end(), std::back_inserter(m_board->partNumber));

    currentString = m_serialNumberTxt->GetValue();
    m_board->serialNumber.clear();
    m_board->serialNumberTL = 0x00 | currentString.length();
    std::copy(currentString.begin(), currentString.end(), std::back_inserter(m_board->serialNumber));

    return true;
}

