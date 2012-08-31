#include "info.h"

BEGIN_EVENT_TABLE(CMyInfo,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyInfo::OnCloseButton)
END_EVENT_TABLE()


CMyInfo::CMyInfo()
:wxDialog(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200,200), wxCLOSE_BOX )
{
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *GridSizer = new wxFlexGridSizer(2,0,0);
	
	wxStaticText *labelname = new wxStaticText(this,wxID_ANY,_("Name"),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labelname,0,wxALL,5);
	
	wxTextCtrl *textname = new wxTextCtrl(this,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->Add(textname,0,wxALL|wxEXPAND,5);
		
		
	wxButton *ButtonClose = new wxButton(this, ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
	MainSizer->Add(GridSizer,1,wxALL|wxEXPAND,0);	
	this->SetSizer(MainSizer);
	this->SetTransparent(100);
	

//	if(GetSizer())
	//	GetSizer()->SetSizeHints(this);
		
	

	
}

CMyInfo::~CMyInfo(void)
{
	
}


void CMyInfo::OnCloseButton(wxCommandEvent &event)
{	
	Destroy();
}

void CMyInfo::OnClose(wxCloseEvent &event)
{
	Destroy();
}
