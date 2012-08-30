#ifndef __INFO
#define __INFO

#include <wx/wx.h>
#include <vector>

class CMyInfo: public wxDialog
{
	
	void OnCloseButton(wxCommandEvent &event);
	//void OnSaveButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
					
public:

	CMyInfo();
	~CMyInfo();
		
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		
		
	};
	
};

#endif