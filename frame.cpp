#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"


BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
	EVT_TEXT(ID_NAME,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_DESCRIPTION,CMyFrame::OnTextChanged)
	EVT_LISTBOX(ID_MARKER_LIST,CMyFrame::OnMarkerList)
	EVT_BUTTON(ID_DELETE,CMyFrame::OnMarkerDelete)
	EVT_BUTTON(ID_NEW_FIELD,CMyFrame::OnNewField)
	EVT_COMMAND_LEFT_CLICK(ID_ICON,CMyFrame::OnLeftClick)
END_EVENT_TABLE()

extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, GetMsg(MSG_MARKER), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxRESIZE_BORDER )
{
	m_DLL = (CDLL*)Parent;
	_ParentPtr = ParentPtr;
	AfterInit = false;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxGREEN);
			
	// Page1
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
		
	GridSizer = new wxFlexGridSizer(2,0,0);
	PanelSizer->Add(GridSizer,1,wxALL|wxEXPAND,5);
	
	// marker name
	wxStaticText *labelname = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labelname,0,wxALL,5);
	textname = new wxTextCtrl(Panel,ID_NAME,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->AddGrowableCol(1);
	GridSizer->AddGrowableRow(1);
	GridSizer->Add(textname,0,wxALL|wxEXPAND,5);
	
	// marker description
	wxStaticText *labeldescription = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DESCRIPTION),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labeldescription,0,wxALL,5);
	textdescription = new wxTextCtrl(Panel,ID_DESCRIPTION,wxEmptyString,wxDefaultPosition,wxSize(200,100),wxTE_MULTILINE);
	GridSizer->Add(textdescription,0,wxALL|wxEXPAND,5);
	

	wxStaticText *labellon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellon,0,wxALL,5);

	textlon = new wxStaticText(Panel,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->Add(textlon,0,wxALL,5);
	
	wxStaticText *labellat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellat,0,wxALL,5);
	
	textlat = new wxStaticText(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(textlat,0,wxALL,5);
	
	wxStaticText *labelicon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_ICON),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labelicon,0,wxALL,5);
	
	wxBitmap bmp(32,23);
	MarkerIcon = new CMyIcon(Panel,this,bmp,ID_ICON,wxEmptyString);
	GridSizer->Add(MarkerIcon,1,wxALL,5);
	
		
	PanelIcon = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,400));
	MainSizer->Add(PanelIcon,1,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelIconSizer = new wxBoxSizer(wxVERTICAL);
	PanelIcon->SetSizer(PanelIconSizer);
	//wxStaticLine *line0 = new wxStaticLine(PanelIcon,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//PanelIconSizer->Add(line0,0,wxALL|wxEXPAND,5);
	
	
	CMarkerIcons *icons =  m_DLL->GetMarkerIcons();

	std::vector<SIcon*>::iterator it = icons->First();
	wxFlexGridSizer *IconGridSizer = new wxFlexGridSizer(7,0,0);
	
	//PanelIconSizer->Add(IconGridSizer,0,wxALL|wxEXPAND,5);
	CMyIcon *selecticon;
	SIcon *Icon;
		
	Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,wxSUNKEN_BORDER);
	MainSizer->Add(Scroll,1,wxALL|wxEXPAND,5);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(IconGridSizer);

	//wxPanel *PanelIcons = new wxPanel(Scroll);
	//PanelIcons->SetSizer(IconGridSizer);
	//PanelIcons->SetBackgroundColour(*wxGREEN);
	//PanelIcons->SetSize(1200,1200);
			

	while(it != icons->Last())
	{
		Icon = *it;
		wxMemoryInputStream in_0((const unsigned char*) Icon->icon, Icon->icon_size);
		wxImage img_0(in_0,wxBITMAP_TYPE_ANY);
		
		if(img_0.IsOk())
		{
			wxBitmap bmp_0(img_0);
			selecticon = new CMyIcon(Scroll,this,bmp_0,Icon->icon_id + ID_ICONSET,wxEmptyString);
			IconGridSizer->Add(selecticon,0,wxALL,5);
		}
	
		it++;
	}
		
	
	Scroll->SetScrollbars(40, 40, 40, 40);
	//Scroll->SetScrollRate (50, 20);


	//wxStaticLine *line1 = new wxStaticLine(PanelIcon,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//PanelIconSizer->Add(line1,0,wxALL|wxEXPAND,5);
	//PanelIcon->Show(false);
		
	Panel->SetSizer(PanelSizer);
		
	//Other
	MainSizer->Add(Panel,0,wxALL|wxEXPAND,5);
	ButtonClose = new wxButton(this,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);

	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();

	//this->SetTransparent(200);
	AfterInit = true;
}

CMyFrame::~CMyFrame(void)
{

}

void CMyFrame::ShowIconChanger(bool show)
{
	PanelIcon->Show(show);
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

}

void CMyFrame::OnPaint(wxPaintEvent &event)
{

	wxPaintDC dc;
	dc.DrawRoundedRectangle(0,0,GetSize().GetWidth(),GetSize().GetHeight(),10);
	//event.Skip();
}

void CMyFrame::OnTextChanged(wxCommandEvent &event)
{	
	if(!AfterInit)
		return;
	
	if(event.GetId() == ID_NAME)
	{
		if(textname->GetValue().Length() >= MARKER_NAME_SIZE)
			ButtonClose->Disable();
		else
			ButtonClose->Enable();
	}

	if(event.GetId() == ID_DESCRIPTION)
	{
		if(textdescription->GetValue().Length() >= MARKER_DESCRIPTION_SIZE)
			ButtonClose->Disable();
		else
			ButtonClose->Enable();
	}
	
	
	// ButtonSave->Enable();
}

void CMyFrame::AddField(wchar_t *name, wchar_t *value)
{
	
	wxPanel *Main = new wxPanel(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	AddFieldSizer->Add(Main,0,wxEXPAND);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *Label = new wxStaticText(Main,wxID_ANY,wxString::Format(_("%s"),name),wxDefaultPosition,wxDefaultSize);
	Sizer->Add(Label,0,wxALL,5);

	Value = new wxTextCtrl(Main,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	Sizer->Add(Value,1,wxALL|wxEXPAND,5);
	wxButton *Delete = new wxButton(Main,ID_DELETE_FIELD,_("-"),wxDefaultPosition,wxSize(22,22));
	Sizer->Add(Delete,0,wxALL,5);
	Main->SetSizer(Sizer);
	
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

}

void CMyFrame::OnNewField(wxCommandEvent &event)
{
	wxTextEntryDialog dlg(this, wxEmptyString, wxEmptyString);
    wxString fieldname; 
		
	
	if (dlg.ShowModal() == wxID_OK)
	{
		AddField(dlg.GetValue().wchar_str(),NULL);
		m_DLL->AddField(dlg.GetValue().wchar_str(),Value->GetValue().wchar_str(),m_DLL->GetSelectedPtr());
	}
	
	
}

void CMyFrame::OnMarkerList(wxCommandEvent &event)
{
	MarkerSelectedPtr = &*(MarkerList->begin() + event.GetSelection());
}

void CMyFrame::OnMarkerDelete(wxCommandEvent &event)
{
	int sel = markerlistbox->GetSelection();
	MarkerList->erase(MarkerList->begin() + sel);
	markerlistbox->Delete(sel);
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{	
	wcscpy_s(MarkerSelectedPtr->name,MARKER_NAME_SIZE, textname->GetValue().wc_str()); 
	wcscpy_s(MarkerSelectedPtr->description, MARKER_DESCRIPTION_SIZE, textdescription->GetValue().wc_str()); 
	Hide();
}

void CMyFrame::OnClose(wxCloseEvent &event)
{
	Hide();
}
void CMyFrame::OnLeftClick(wxCommandEvent &event)
{
	
}
void CMyFrame::ShowWindow(bool show)
{
	if(show)
	{
		
		ParentX = _ParentPtr->GetScreenPosition().x;
		ParentY = _ParentPtr->GetScreenPosition().y;
		
		double to_x, to_y;
		MarkerSelectedPtr = m_DLL->GetSelectedPtr();
		m_DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
	
		double vm[4];
		m_DLL->GetBroker()->GetVisibleMap(vm);
		
		float scale = m_DLL->GetBroker()->GetMapScale();
		wxPoint pt;
		pt.x = (int)((-vm[0] + MarkerSelectedPtr->x) * scale) + ParentX;
		pt.y = (int)((-vm[1] + MarkerSelectedPtr->y) * scale) + ParentY;
			
		this->SetPosition(pt);
		textname->SetValue(wxString::Format(_("%s"),MarkerSelectedPtr->name));
		textdescription->SetValue(wxString::Format(_("%s"),MarkerSelectedPtr->description));
		
		textlon->SetLabel(FormatLongitude(to_x));
		textlat->SetLabel(FormatLatitude(-to_y));

		SIcon *Icon =  m_DLL->GetMarkerIcon(MarkerSelectedPtr->icon_id);
		if(Icon != NULL)
		{
			wxMemoryInputStream in_0((const unsigned char*)Icon->icon, Icon->icon_size);
			wxImage img_0(in_0,wxBITMAP_TYPE_ANY);
			if(img_0.IsOk())
			{
				wxBitmap bmp_0(img_0);
				MarkerIcon->SetBitmap(bmp_0);
			}
		}

		Scroll->SetFocusIgnoringChildren();
	}
	
	Show(show);
}
void CMyFrame::SetMarkerIcon(int id)
{
	SIcon *Icon = m_DLL->GetMarkerIcon( id );
	
	if(Icon == NULL)
			return;
		
	// podmiana ikonki w renderze
	m_DLL->SetMarkerTextureID(Icon->texture_id);
	m_DLL->SetMarkerIconID(Icon->icon_id);
	m_DLL->GetBroker()->Refresh(m_DLL->GetBroker()->GetParentPtr());
		
	// zmiana ikonki na framie
	wxMemoryInputStream in_0((const unsigned char*)Icon->icon, Icon->icon_size);
	wxImage img_0(in_0,wxBITMAP_TYPE_ANY);
	wxBitmap bmp_0(img_0);
	MarkerIcon->SetBitmap(bmp_0);
	MarkerIcon->Update();
}


BEGIN_EVENT_TABLE(CMyIcon,wxStaticBitmap)
	EVT_MOUSE_EVENTS(CMyIcon::OnMouse)
	EVT_LEAVE_WINDOW(CMyIcon::OnWindowLeave)
	EVT_ENTER_WINDOW(CMyIcon::OnWindowEnter)
END_EVENT_TABLE()

int CMyIcon::icon_counter = 0;
CMyIcon::CMyIcon(wxWindow *Parent, CMyFrame *frame, wxBitmap bmp, wxWindowID id,wxString name)
:wxStaticBitmap(Parent,id,bmp,wxDefaultPosition,wxDefaultSize)
{
	icon_counter++;
	m_Frame = frame;
	this->SetBackgroundColour(wxColor(200,200,200));
	this->SetCursor(wxCursor(wxCURSOR_HAND));
	showicons_panel = false;
	//SetToolTip(name);
}

CMyIcon::~CMyIcon()
{
}

void CMyIcon::OnMouse(wxMouseEvent &event)
{
	
	
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
	
}
void CMyIcon::OnWindowLeave(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(200,200,200));
	SetSize(32,32);
	Refresh();
}

void CMyIcon::OnWindowEnter(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(255,255,255));
	SetSize(34,34);
	Refresh();
}
