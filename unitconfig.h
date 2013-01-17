#ifndef __UNITCONFIG
#define __UNITCONFIG

#include <wx/wx.h>
#include <vector>

class CUnitConfig: public wxDialog
{
	
	size_t Unit;
	wxArrayPtrVoid Radios;
	void OnRadio(wxCommandEvent &event);
						
public:

	CUnitConfig();
	~CUnitConfig();
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