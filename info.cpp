#include <wx/hyperlink.h>
#include "info.h"
#include "tools.h"

//BEGIN_EVENT_TABLE(CMyInfo,wxDialog)

//END_EVENT_TABLE()


CMyInfo::CMyInfo(CDLL *Parent)
:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{
	m_DLL = Parent;

	//this->SetForegroundColour(*wxRED);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);
	
	CMyButton *ButtonDelete = new CMyButton(this,GetMsg(MSG_DELETE_MARKER));
	TopSizer->Add(ButtonDelete,0,wxALL|wxEXPAND,2);
		
	wxHyperlinkCtrl *ButtonProperties = new wxHyperlinkCtrl(this,wxID_CANCEL,GetMsg(MSG_PROPERTIES_MARKER),wxEmptyString);
	TopSizer->Add(ButtonProperties,0,wxALL,2);
	
	wxHyperlinkCtrl *ButtonClose = new wxHyperlinkCtrl(this,wxID_CANCEL,GetMsg(MSG_CLOSE),wxEmptyString);
	TopSizer->Add(ButtonClose,0,wxALL,2);

	wxStaticText *labellon = new wxStaticText(this,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(labellon,0,wxALL,5);

	textlon = new wxStaticText(this,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	TopSizer->Add(textlon,0,wxALL,5);
	
	wxStaticText *labellat = new wxStaticText(this,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(labellat,0,wxALL,5);
	
	textlat = new wxStaticText(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(textlat,0,wxALL,5);

	this->SetSizer(TopSizer);

	//this->SetBackgroundColour(wxColor(200,200,200));
	//this->SetTransparent(200);
	
	
}

CMyInfo::~CMyInfo()
{
}

//void CMyInfo::OnPaint(wxPaintEvent &event)
//{
	//wxWindowDC *dc;
	//dc.
//}

//void CMyInfo::ShowPopupMenu()
//{	
	//wxMenu *menu  = new wxMenu();
	//menu->Append(123,_("abc"));
	//PopupMenu(menu);
//}


void CMyInfo::ShowWindow(bool show)
{
	Show(show);
	
	if(!show)
		return;

	double to_x, to_y;
	SMarker *MarkerSelectedPtr = m_DLL->GetSelectedPtr();
	int ParentX = ((wxWindow*)m_DLL->GetBroker()->GetParentPtr())->GetScreenPosition().x;
	int ParentY = ((wxWindow*)m_DLL->GetBroker()->GetParentPtr())->GetScreenPosition().y;
		
	MarkerSelectedPtr = m_DLL->GetSelectedPtr();
	m_DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
	
	double vm[4];
	m_DLL->GetBroker()->GetVisibleMap(vm);
		
	float scale = m_DLL->GetBroker()->GetMapScale();
	wxPoint pt;
	pt.x = (int)((-vm[0] + MarkerSelectedPtr->x) * scale) + ParentX;
	pt.y = (int)((-vm[1] + MarkerSelectedPtr->y) * scale) + ParentY;
			
	this->SetPosition(pt);

	m_DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
	textlon->SetLabel(FormatLongitude(to_x));
	textlat->SetLabel(FormatLongitude(-to_y));
	
}

BEGIN_EVENT_TABLE(CMyButton,wxWindow)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_LEAVE_WINDOW(OnWindowLeave)
	EVT_ENTER_WINDOW(OnWindowEnter)
END_EVENT_TABLE()

CMyButton::CMyButton(wxWindow *Parent,wxString text)
:wxPanel(Parent,12, wxDefaultPosition, wxDefaultSize )
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	//wxHyperlinkCtrl *Button = new wxHyperlinkCtrl(this,wxID_CANCEL,text,wxEmptyString);
	wxStaticText *Button = new wxStaticText(this,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(Button,0,wxALL,10);
	
	this->SetSizer(Sizer);
	this->SetSize(100,50);
	SetBackgroundColour(wxColor(255,255,255));
}

CMyButton::~CMyButton()
{

}

void CMyButton::OnMouse(wxMouseEvent &event)
{
	
	/*
	if(event.LeftDown())
	{
		
		if(event.GetId() ==  ID_ICON)
		{
			showicons_panel = !showicons_panel;
			m_Frame->ShowIconChanger(showicons_panel);
			return;
		}
	
		if((event.GetId() >= ID_ICONSET) && (event.GetId() < ID_ICONSET + icon_counter))
			m_Frame->SetMarkerIcon(event.GetId() - ID_ICONSET);
		
	}
	event.Skip();
	*/
	
}
void CMyButton::OnWindowLeave(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(200,200,200));
	//SetSize(32,32);
	Refresh();
}

void CMyButton::OnWindowEnter(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(255,255,255));
	//SetSize(34,34);
	Refresh();
}
