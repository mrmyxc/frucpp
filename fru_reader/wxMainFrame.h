#pragma once
#include "wx/wx.h"

class wxMainFrame : public wxFrame
{
public:
	wxMainFrame();
	~wxMainFrame();

private:
	wxMenuBar * m_menuBar;
	wxMenu * m_fileMenu;
	wxMenu * m_optionsMenu;
	wxMenu * m_aboutMenu;

	wxListBox * m_mainListBox;
};

