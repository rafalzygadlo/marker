#ifndef __INFO
#define __INFO

#include <wx/wx.h>
#include <vector>
#include "dll.h"

class CDLL;
class CMyInfo: public wxDialog
{
	CDLL *m_DLL;
	wxStaticText *textlat, *textlon;
						
public:

	CMyInfo(CDLL *Parent);
	~CMyInfo();
	void ShowWindow(bool show);
	
	//DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		
		
	};
	
};

class CMyButton: public wxPanel
{
	
	void OnMouse(wxMouseEvent &event);
	void OnWindowLeave(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);
					
public:

	CMyButton(wxWindow *Parent, wxString text);
	~CMyButton();
	DECLARE_EVENT_TABLE();
	
};



#endif