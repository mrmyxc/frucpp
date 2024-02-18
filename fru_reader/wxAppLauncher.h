#pragma once

#include "wx/wx.h"
#include "wxMainFrame.h"

class wxAppLauncher : public wxApp
{
public:
	wxAppLauncher();
	~wxAppLauncher();

public:
	virtual bool OnInit();

private:
	wxMainFrame* m_frame;
};

