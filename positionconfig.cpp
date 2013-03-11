#include <wx/hyperlink.h>
#include "positionconfig.h"
#include "tools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CPositionConfig,wxDialog)
	EVT_TEXT(ID_LON,CPositionConfig::OnLon)
	EVT_TEXT(ID_LAT,CPositionConfig::OnLat)
	EVT_BUTTON(ID_OK,CPositionConfig::OnOk)
	EVT_BUTTON(ID_CANCEL,CPositionConfig::OnCancel)
END_EVENT_TABLE()

CPositionConfig::CPositionConfig(CDLL *Parent)
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
	_Parent = Parent;	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxStaticText *info = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_POSITION_INFO),wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(info,0,wxALL,5);
	
	wxStaticText *labellat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(labellat,0,wxALL,5);
	textlat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	
	PanelSizer->Add(textlat,0,wxALL,5);
	
	wxStaticText *labellon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(labellon,0,wxALL,5);

	textlon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	PanelSizer->Add(textlon,0,wxALL,5);
	

	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	
	wxButton *ButtonOk = new wxButton(this,ID_OK,GetMsg(MSG_OK));
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	
	wxButton *ButtonCancel = new wxButton(this,ID_CANCEL,GetMsg(MSG_CANCEL));
	ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	this->SetSizer(MainSizer);

	GetSizer()->SetSizeHints(this);
	Center();
	
}

CPositionConfig::~CPositionConfig()
{
	
}

void CPositionConfig::OnOk(wxCommandEvent &event)
{
	_Parent->Append();
	this->Hide();
}

void CPositionConfig::OnCancel(wxCommandEvent &event)
{
	_Parent->Remove();
	this->Hide();
}

void CPositionConfig::OnLon(wxCommandEvent &event)
{
	SMarker *MarkerSelectedPtr =_Parent->GetNewMarkerPtr();
	if(MarkerSelectedPtr == NULL)
		return;

	float value = MarkerSelectedPtr->x;
		
	if(SetLon(textlon->GetValue().char_str(),&value))
	{
		double y,to_x,to_y;
		_Parent->GetBroker()->Unproject(value,y,&to_x,&to_y);
		MarkerSelectedPtr->x = (float)to_x;
					
		_Parent->GetBroker()->Refresh(_Parent->GetBroker()->GetParentPtr());
		textlon->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		textlon->Refresh();

	}else{
		
		textlon->SetForegroundColour(*wxRED);
		textlon->Refresh();
	
	}

}

void CPositionConfig::OnLat(wxCommandEvent &event)
{
	SMarker *MarkerSelectedPtr =_Parent->GetNewMarkerPtr();
	if(MarkerSelectedPtr == NULL)
		return;
	
	float value = MarkerSelectedPtr->x;
	
	if(SetLat(textlat->GetValue().char_str(),&value))
	{
		double x,to_x,to_y;
		x = MarkerSelectedPtr->x;
		_Parent->GetBroker()->Unproject(x,value,&to_x,&to_y);
		MarkerSelectedPtr->y = (float)to_y;
					
		_Parent->GetBroker()->Refresh(_Parent->GetBroker()->GetParentPtr());
		textlat->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		textlat->Refresh();

	}else{
		
		textlat->SetForegroundColour(*wxRED);
		textlat->Refresh();
	}

}

void CPositionConfig::SetPosition(double lon, double lat)
{
	textlon->SetValue(FormatLongitude(lon));
	textlat->SetValue(FormatLatitude(lat));
}

