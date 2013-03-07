#ifndef __POSITIONCONFIG
#define __POSITIONCONFIG

#include <wx/wx.h>
#include <vector>
#include <wx/spinctrl.h>

class CPositionConfig: public wxDialog
{
	
	size_t Unit;
	wxArrayPtrVoid Radios;
	wxTextCtrl *textlon;
	wxTextCtrl *textlat;
	void OnRadio(wxCommandEvent &event);
						
public:

	CPositionConfig();
	~CPositionConfig();
	void SetPosition(double lon, double lat);
		
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		ID_RADIO,
		ID_LON,
		ID_LAT
		
		
	};
	
};

#endif