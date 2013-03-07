#include <wx/hyperlink.h>
#include "positionconfig.h"
#include "tools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CPositionConfig,wxDialog)
END_EVENT_TABLE()

CPositionConfig::CPositionConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
		
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	
	wxFont font;
	font.SetPointSize(14);
	wxStaticText *info = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_POSITION_INFO),wxDefaultPosition,wxDefaultSize);
	info->SetFont(font);
	PanelSizer->Add(info,0,wxALL,5);
	
	wxStaticText *labellat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(labellat,0,wxALL,5);
	textlat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
	
	PanelSizer->Add(textlat,0,wxALL,5);
	
	wxStaticText *labellon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(labellon,0,wxALL,5);

	textlon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_READONLY);
	PanelSizer->Add(textlon,0,wxALL,5);
	

	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_OK));
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	
	wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CANCEL));
	ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	this->SetSizer(MainSizer);

	GetSizer()->SetSizeHints(this);
	Center();
	
}

CPositionConfig::~CPositionConfig()
{
	Radios.Clear();
}

void CPositionConfig::SetPosition(double lon, double lat)
{
	textlon->SetValue(FormatLongitude(lon));
	textlat->SetValue(FormatLatitude(lat));
}

