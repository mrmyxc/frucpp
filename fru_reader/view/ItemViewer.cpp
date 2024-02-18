#pragma once
#include "ItemViewer.h"

ItemViewer::ItemViewer(wxWindow * parent, wxWindowID id, InfoArea * area, std::vector<FD::Unit> * units) : wxPanel(parent, id), m_infoArea(area), m_units(units)
{
    wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxListBox * m_listBox = new wxListBox(this, wxID_ANY);
    m_listBox->Bind(wxEVT_LISTBOX, &ItemViewer::OnItemSelected, this);
    sizer->Add(m_listBox, wxSizerFlags(1).Expand());

    if (m_units != nullptr)
    {
        for (auto it = m_units->begin(); it != m_units->end(); it++)
        {
            if (it->header.boardArea)
            {
                m_listBox->Append(wxString(it->boardArea.productName.data(), (it->boardArea.productNameTL & 0x3F)));
            }
        }
    }

    m_addButton = new wxButton(this, wxID_ANY, "Add");
    m_removeButton = new wxButton(this, wxID_ANY, "Delete");
    m_saveButton = new wxButton(this, wxID_ANY, "Save");
    m_saveButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ItemViewer::OnSaveButtonClicked, this);
    buttonSizer->Add(m_addButton, wxSizerFlags(1));
    buttonSizer->Add(m_removeButton, wxSizerFlags(1));
    buttonSizer->Add(m_saveButton, wxSizerFlags(1));
    sizer->Add(buttonSizer, wxSizerFlags(0).Center());
    
    this->FitInside();
    this->SetSizerAndFit(sizer);
}

ItemViewer::~ItemViewer()
{
}

void ItemViewer::OnItemSelected(wxCommandEvent & event)
{
    std::cout << "Item Selected" << "\n";

    if (m_units != nullptr)
    {
        wxString selection = event.GetString();

        for (auto & thing : *m_units)
        {
            if (thing.header.boardArea)
            {
                wxString board = wxString(thing.boardArea.productName.data(), (thing.boardArea.productNameTL & 0x3F));
                int comp = selection.CompareTo(board);
                if (comp == 0)
                {
                    if (thing.isEdited)
                    {
                        // Bring up a dialog box asking to save or not before switching
                    }

                    m_infoArea->SetInfo(&thing);
                    break;
                }
            }
        }
    }
}

void ItemViewer::OnSaveButtonClicked(wxCommandEvent & event)
{
    m_infoArea->SaveInfo();
}
