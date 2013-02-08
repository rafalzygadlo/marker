#include <wx/hyperlink.h>
#include "positionconfig.h"
#include "tools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CPositionConfig,wxDialog)
	EVT_RADIOBUTTON(wxID_ANY,CPositionConfig::OnRadio)
END_EVENT_TABLE()

CPositionConfig::CPositionConfig()
:wxDialog( NULL,wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize )
{
		
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(wxColor(255,255,255));
	Panel->SetSizer(PanelSizer);
	
	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	PanelSizer->Add(HSizer,0,wxALL,5);
	
	wxSpinCtrl *Spin1 = new wxSpinCtrl(Panel,wxID_ANY,_("text"));
	HSizer->Add(Spin1,0,wxALL,5);
	Spin1->SetMin(0);
	Spin1->SetMax(180);
	

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

void CPositionConfig::OnRadio(wxCommandEvent &event)
{
	Unit = event.GetId() - ID_RADIO;
}

size_t CPositionConfig::GetUnit()
{
	return Unit;
}

void CPositionConfig::SetUnit(size_t val)
{
	
	
	
}
