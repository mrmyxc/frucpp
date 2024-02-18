#include "wxAppLauncher.h"
#include "wx/wx.h"
#include "wxMainFrame.h"

wxIMPLEMENT_APP(wxAppLauncher);

wxAppLauncher::wxAppLauncher()
{
}

wxAppLauncher::~wxAppLauncher()
{
}

bool wxAppLauncher::OnInit()
{
	m_frame = new wxMainFrame();
	m_frame->Show();
	return true;
}
