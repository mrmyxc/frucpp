#include "wxMainFrame.h"
#include "model/Unit.h"
#include "view/CommonHeaderWindow.h"
#include "view/ItemViewer.h"
#include "view/InternalUseAreaWindow.h"
#include "view/InfoArea.h"
#include <vector>
#include <memory>

wxMainFrame::wxMainFrame() : wxFrame(nullptr, wxID_ANY, "Main Title", wxPoint(0,0), wxSize(800, 600))
{
    std::vector<FD::Unit> * listOfUnits = new std::vector<FD::Unit>();

    std::vector<uint8_t> data2
    {
        0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFE,
        0x01,
        0x07,
        0x19,
        0x00, 0x00, 0x00,
        0xCA, 'T', 'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'y',
        0xCA, 'P', 'R', 'O', 'D', 'U', 'C', 'T', ' ', 'A', '1',
        0xCA, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        0xCA, 'D', 'E', 'V', 'I', 'C', 'E', ' ', 'A', '1', '1',
        0xC0,
        0xC1,
        0x00,
        0x00,
        0x00,
        0xFF
    };

    std::vector<uint8_t> data3
    {
        0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFE,
        0x01,
        0x07,
        0x19,
        0x00, 0x00, 0x00,
        0xCA, 'T', 'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'y',
        0xCA, 'P', 'R', 'O', 'D', 'U', 'C', 'T', ' ', 'B', '2',
        0xCA, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        0xCA, 'D', 'E', 'V', 'I', 'C', 'E', ' ', 'A', '2', '2',
        0xC0,
        0xC1,
        0x00,
        0x00,
        0x00,
        0xB2
    };

    auto placeHolder = FD::Unit();
  
    placeHolder.SetData(data2);
    listOfUnits->push_back(placeHolder);

    placeHolder.SetData(data3);
    listOfUnits->push_back(placeHolder);

    m_menuBar = new wxMenuBar();

    m_fileMenu = new wxMenu();
    m_fileMenu->Append(wxID_OPEN, _T("&Open"));
    m_fileMenu->Append(wxID_OPEN, _T("&Save"));
    m_fileMenu->AppendSeparator();
    m_fileMenu->Append(wxID_EXIT, _T("&Quit"));
    m_menuBar->Append(m_fileMenu, _T("&File"));

    m_aboutMenu = new wxMenu();
    m_aboutMenu->Append(wxID_ABOUT, _T("&About"));
    m_menuBar->Append(m_aboutMenu, _T("&Help"));

    SetMenuBar(m_menuBar);

    wxBoxSizer * mainBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    InfoArea * ia = new InfoArea(this, wxID_ANY);
    ItemViewer * itv = new ItemViewer(this, wxID_ANY, ia, listOfUnits);

    mainBoxSizer->Add(itv, wxSizerFlags(1).Expand().Border( wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5));
    mainBoxSizer->Add(ia, wxSizerFlags(5).Expand().Border(wxRIGHT | wxTOP | wxBOTTOM, 5));

    mainBoxSizer->SetMinSize(wxSize(800, 600));
    SetSizerAndFit(mainBoxSizer);

    CreateStatusBar(3);
    SetStatusText(wxT("Ready"), 0);
}

wxMainFrame::~wxMainFrame()
{
}
