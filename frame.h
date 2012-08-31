#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/mstream.h>
#include "conf.h"
#include "dll.h"
#include <vector>

class CMyIcon;
class CMyFrame: public wxDialog
{
	wxScrolledWindow *Scroll;
	CDLL *m_DLL;	
	SMarker *MarkerSelectedPtr;
	wxTextCtrl *textname;
	std::vector<SMarker> *MarkerList;
	wxListBox *markerlistbox;
	wxFlexGridSizer *GridSizer;
	wxPanel *Panel;
	wxBoxSizer *AddFieldSizer;
	wxTextCtrl *Value;
	wxTextCtrl *textdescription;
	wxButton *ButtonClose;
	wxPanel *PanelIcon;
	CMyIcon *MarkerIcon;
	wxStaticText *textlon;
	wxStaticText *textlat;
	int ParentX, ParentY;
	wxWindow *_ParentPtr;

	bool AfterInit;

	void AddField(wchar_t *name, wchar_t *value);
	void AddIconControls();
	
	void OnCloseButton(wxCommandEvent &event);
	//void OnSaveButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnMarkerList(wxCommandEvent &event);
	void OnMarkerDelete(wxCommandEvent &event);
	void OnNewField(wxCommandEvent &event);
	void OnTextChanged(wxCommandEvent &event);
	void OnLeftClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
					
public:

	void ShowIconChanger(bool show);
	void SetMarkerIcon(int id);
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
		
	DECLARE_EVENT_TABLE();

	
};

class CMyIcon: public wxStaticBitmap
{

	CMyFrame *m_Frame;
	static int icon_counter;
	bool showicons_panel;
	void OnMouse(wxMouseEvent &event);
	void OnWindowLeave(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);
	
public:
		
	CMyIcon(wxWindow *Parent, CMyFrame *frame,wxBitmap bmp,wxWindowID id,wxString name);
		~CMyIcon();
		DECLARE_EVENT_TABLE();

};

enum
	{
		ID_CLOSE = 1234,
		ID_SAVE,
		ID_NAME,
		ID_DESCRIPTION,
		ID_MARKER_LIST,
		ID_DELETE,
		ID_NEW_FIELD,
		ID_DELETE_FIELD,
		ID_ICON,
		ID_CHANGE_ICON,
		ID_ICONSET,
		
	};

#endif