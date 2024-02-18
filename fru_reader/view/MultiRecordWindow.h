#pragma once
#include "wx/wx.h"
#include "../model/Unit.h"

class MultiRecordWindow : public wxStaticBox
{
public:
    MultiRecordWindow(wxWindow * parent, wxWindowID id);
    ~MultiRecordWindow();
    bool SetInfo(std::vector<FD::MultiRecordArea> * unit);

private:
    std::vector<FD::MultiRecordArea> * m_multiRecords;
    wxListBox * m_multiRecordList;
    wxTextCtrl * m_typeTxt;
    wxCheckBox * m_endOfList;
    wxTextCtrl * m_lengthTxt;
    wxTextCtrl * m_recordChecksumTxt;
    wxTextCtrl * m_headerChecksumTxt;

    wxTextCtrl * m_multiRecordData;
    wxTextCtrl * m_multiRecordDataTranslation;
};
