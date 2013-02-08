#ifndef __POSITIONCONFIG
#define __POSITIONCONFIG

#include <wx/wx.h>
#include <vector>
#include <wx/spinctrl.h>

class CPositionConfig: public wxDialog
{
	
	size_t Unit;
	wxArrayPtrVoid Radios;
	void OnRadio(wxCommandEvent &event);
						
public:

	CPositionConfig();
	~CPositionConfig();
	void SetUnit(size_t val);
	size_t GetUnit();
	
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		ID_RADIO,
		
		
	};
	
};

#endif