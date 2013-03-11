#ifndef __POSITIONCONFIG
#define __POSITIONCONFIG

#include <wx/wx.h>
#include <vector>
#include <wx/spinctrl.h>
#include "dll.h"

class CDLL;
class CPositionConfig: public wxDialog
{
	CDLL *_Parent;
	size_t Unit;
	wxArrayPtrVoid Radios;
	wxTextCtrl *textlon;
	wxTextCtrl *textlat;
	void OnLon(wxCommandEvent &event);
	void OnLat(wxCommandEvent &event);
	void OnOk(wxCommandEvent &event);
	void OnCancel(wxCommandEvent &event);
						
public:

	CPositionConfig(CDLL *Parent);
	~CPositionConfig();
	void SetPosition(double lon, double lat);
		
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		ID_RADIO,
		ID_LON,
		ID_LAT,
		ID_OK,
		ID_CANCEL
		
	};
	
};

#endif