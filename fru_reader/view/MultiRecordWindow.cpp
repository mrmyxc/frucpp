#pragma once
#include "MultiRecordWindow.h"
#include "wx/stc/stc.h"

MultiRecordWindow::MultiRecordWindow(wxWindow * parent, wxWindowID id) : wxStaticBox(parent, id, "Multi Record Area")
{
    wxBoxSizer * mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer * headerContainer = new wxFlexGridSizer(2);
    wxScrolledWindow * dataContainer = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer * dataContainerSizer = new wxBoxSizer(wxHORIZONTAL);

    m_multiRecords = nullptr;

    m_multiRecordList = new wxListBox(this, wxID_ANY);
    m_multiRecordList->Disable();

    m_multiRecordData = new wxTextCtrl(dataContainer, wxID_ANY);
    m_multiRecordDataTranslation = new wxTextCtrl(dataContainer, wxID_ANY);
    m_multiRecordData->Disable();
    m_multiRecordDataTranslation->Disable();
    
    // Header
    wxStaticText * type = new wxStaticText(this, wxID_ANY, "type");
    m_typeTxt = new wxTextCtrl(this, wxID_ANY, "type");
    m_endOfList = new wxCheckBox(this, wxID_ANY, "endOfList");
    wxStaticText * length = new wxStaticText(this, wxID_ANY, "length");
    m_lengthTxt = new wxTextCtrl(this, wxID_ANY, "length");
    wxStaticText * recordChecksum = new wxStaticText(this, wxID_ANY, "recordChecksum");
    m_recordChecksumTxt = new wxTextCtrl(this, wxID_ANY, "recordChecksum");
    wxStaticText * headerChecksum = new wxStaticText(this, wxID_ANY, "headerChecksum");
    m_headerChecksumTxt = new wxTextCtrl(this, wxID_ANY, "headerChecksum");
    
    m_typeTxt->Disable();
    m_lengthTxt->Disable();
    m_recordChecksumTxt->Disable();
    m_headerChecksumTxt->Disable();

    headerContainer->Add(type, wxSizerFlags(1));
    headerContainer->Add(m_typeTxt, wxSizerFlags(1).Expand());
    headerContainer->Add(m_endOfList, wxSizerFlags(1));
    headerContainer->Add(0, 0); // Dummy to get to new line
    headerContainer->Add(length, wxSizerFlags(1).Expand());
    headerContainer->Add(m_lengthTxt, wxSizerFlags(1));
    headerContainer->Add(recordChecksum, wxSizerFlags(1).Expand());
    headerContainer->Add(m_recordChecksumTxt, wxSizerFlags(1).Expand());
    headerContainer->Add(headerChecksum, wxSizerFlags(1).Expand());
    headerContainer->Add(m_headerChecksumTxt, wxSizerFlags(1).Expand());

    dataContainer->SetScrollbars(10, 10, 100, 100);
    dataContainer->SetSizer(dataContainerSizer);
    dataContainer->FitInside();
    dataContainer->SetScrollRate(5, 5);

    dataContainerSizer->Add(m_multiRecordData, wxSizerFlags(1).Border(wxLEFT | wxRIGHT, 5).Expand());
    dataContainerSizer->Add(m_multiRecordDataTranslation, wxSizerFlags(1).Border(wxLEFT | wxRIGHT, 5).Expand());

    mainSizer->Add(0, 0, wxSizerFlags(0).Border(wxLEFT, 10)); // Add dummy object to align texts
    mainSizer->Add(m_multiRecordList, wxSizerFlags(1).Expand().Border(wxTOP | wxBOTTOM, 15));
    mainSizer->Add(headerContainer, wxSizerFlags(2).Expand().Border(wxALL, 15));
    mainSizer->Add(dataContainer, wxSizerFlags(5).Expand().Border(wxTOP | wxBOTTOM, 15));
    this->SetSizer(mainSizer);
}

MultiRecordWindow::~MultiRecordWindow()
{
}

bool MultiRecordWindow::SetInfo(std::vector<FD::MultiRecordArea> * unit)
{
    return true;
}