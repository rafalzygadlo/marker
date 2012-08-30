#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include "icons.h"

#define BUFSIZE 512

CNaviBroker *BrokerPtr;
CNaviMapIOApi *ThisPtr;

CDLL::CDLL(CNaviBroker *NaviBroker)	:CNaviMapIOApi(NaviBroker)
{
		
	Broker = NaviBroker;
	ConfigPath = wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(MARKER_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("marker"),wxEmptyString,ConfigPath,wxEmptyString);
	PointsPath = wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(MARKER_DATA_FILE));
	
	HotSpotX = HotSpotY = 0;
	SelectedIconID = 0;
	SelectedTextureID = 0;
	Angle = 0.0;
	Factor = DEFAULT_FACTOR; 
	MoveMarker = false;
	ErrorCode = 0;
	MouseX = 0;
	MouseY = 0;
	Type = BUTTON_TYPE_ANY;
	RectWidth = 0; 
	RectHeight = 0;
	TranslationX = 0;
	TranslationY = 0;
	MapScale = 0;
	ClickedOnButton = false;
	FirstTime = true;
	ButtonAction = BUTTON_TYPE_ANY;
	MapX = 0.0;
	MapY = 0.0;
	FirstRun = true;
	ShowWindow = false;
	
	MarkerIcons = new CMarkerIcons();
	
	SelectedPtr = NULL;
	DBLClick = false;

	this->AddExecuteFunction("marker_MarkerNew", MarkerNew);
	this->AddExecuteFunction("marker_MarkerGet",MarkerGet);
	this->AddExecuteFunction("marker_MarkerCount",MarkerCount);
	Font = new CNaviPixmapFont(FONT_NAME,FONT_SIZE);
	MyFrame = NULL;
	MyInfo = NULL;
	
	
	CreateApiMenu();

}

CDLL::~CDLL()
{
	WriteConfig();
	delete FileConfig;
	delete Font;
	delete MarkerIcons;
}

SMarker *CDLL::GetSelectedPtr()
{
	return SelectedPtr;
}

CMarkerIcons *CDLL::GetMarkerIcons()
{
	return MarkerIcons;
}

size_t CDLL::GetMarkerIconsCount()
{
	return MarkerIcons->Count();
}

SIcon *CDLL::GetMarkerIcon(int id)
{
	return MarkerIcons->GetItem(id);
}
void CDLL::SetMarkerTextureID(int id)
{
	SelectedTextureID = id;
	SelectedPtr->texture_id = id;
}

void CDLL::SetMarkerIconID(int id)
{
	SelectedIconID = id;
	SelectedPtr->icon_id = id;
}


void CDLL::SetSmoothScaleFactor(double _Scale) 
{
	if( _Scale > Factor )
		SmoothScaleFactor = _Scale;
	else
		SmoothScaleFactor = Factor;
}

wxString CDLL::GetWorkDir(void)
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
	buffer.Printf(wxT("%s%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	delete Paths;
	return buffer;
}

void CDLL::ReadConfig()
{
	
	FileConfig->Read(_(KEY_FILEPATH), &FilePath);
	
	if(_file.Exists(PointsPath))
	{
		
		if(_file.Open(PointsPath))
		{	
			ReadHeader();
			SMarker *buffer = (SMarker*)malloc(sizeof(SMarker));
			memset(buffer,0,sizeof(SMarker));
			while(!_file.Eof())
			{	
				_file.Read(buffer,sizeof(SMarker));
				Add(buffer->x,buffer->y,buffer->icon_id, buffer->name,buffer->description,buffer->type);
				
			}
		
			_file.Close();
		}
	}
}

void CDLL::ReadHeader()
{
	SMarkerHeader *header_buffer = (SMarkerHeader*)malloc(sizeof(SMarkerHeader));
	_file.Read(header_buffer,sizeof(SMarkerHeader));
	
}

void CDLL::WriteConfig()
{
	FileConfig->Write(_(KEY_FILEPATH), FilePath);
	
	if(_file.Open(PointsPath,wxFile::write))
	{
		WriteHeader();
		
		std::vector<SMarker> points = GetPoints();
		for(unsigned int i = 0; i < points.size();i++)
//		{
			_file.Write(&points[i],sizeof(SMarker));

//			SFields *field = points[i].field;
//			if(field != NULL)
//			{
//				_file.Write(field,sizeof(SFields));
//				while(field->next != NULL)
//				{
//					_file.Write(field->next,sizeof(SFields));
//					field = field->next;
//				}
//			}
//		}
			
		_file.Close();
	}
	
}

void CDLL::WriteHeader()
{
	SMarkerHeader Header;
	Header.version = MARKER_HEADER_VERSION;
	_file.Write(&Header,sizeof(SMarkerHeader));
}

CNaviBroker *CDLL::GetBroker()
{
	return Broker;
}

wxString CDLL::GetFilePath()
{
	return FilePath;
}

void CDLL::SetFilePath(wxString file)
{
	FilePath = file;
}

void CDLL::SetButtonAction(int action)
{
	ButtonAction = action;
}

void CDLL::Run(void *Params)
{
	ThisPtr = (CNaviMapIOApi*)this;

}

void CDLL::Kill(void)
{
	NeedExit = true;
	delete MyInfo;
	delete MyFrame;
	//DataThread->Delete();
	//Broker->FreeInstance(this);
	WriteConfig();

};

bool CDLL::GetNeedExit(void) 
{
	return NeedExit;
};

wxArrayString *CDLL::GetDataArray()
{
	return &DataArray;
};

std::vector<SMarker> *CDLL::GetMarkerList()
{
	return &vPoints;
}

void CDLL::Config()
{
//	MyFrame = new CMyFrame();
//	MyFrame->ShowModal();
//	MyFrame->Destroy();
//	MyFrame = NULL;

}

void CDLL::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
		
	
	// move marker RMB need this
	// . . . . . . . . . . . . . . . . . . . . 	
	double mom[2];
	double _x,_y;
	
	Broker->GetMouseOM(mom);
	MapScale = Broker->GetMapScale();
	Broker->Unproject(mom[0],mom[1],&_x,&_y);
	_y = _y *-1;
	
	MapX = _x;
	MapY = _y;
	// . . . . . . . . . . . . . . . . . . . . 	
	
	if(!lmb)
		return;

	ShowFrameWindow(false);	
	std::vector<SMarker>::iterator it;
	it = vPoints.begin();
	while(it != vPoints.end())
	{
		if(IsPointInsideBox(_x, _y, it->x - TranslationX, it->y - TranslationY, it->x + RectWidth-TranslationX , it->y + RectHeight-TranslationY))
		{
			SelectedPtr =  &*it;
			//this->ShowInfoWindow(true);
			ShowFrameWindow(true);
			return;
		}
		
		it++;
	}
	SelectedPtr = NULL;
}

void CDLL::ShowInfoPopupMenu()
{
	if(MyInfo == NULL)
		MyInfo = new CMyInfo(this);
	MyInfo->ShowPopupMenu();
}

void CDLL::ShowFrameWindow(bool show)
{
	if(MyFrame == NULL)
		MyFrame = new CMyFrame(this,(wxWindow*)Broker->GetParentPtr());
	MyFrame->ShowWindow(show);
}

void CDLL::ShowInfoWindow(bool show)
{
	
	if(MyInfo == NULL)
		MyInfo = new CMyInfo(this);
	MyInfo->ShowWindow(show);
}


void CDLL::MouseDBLClick(int x, int y)
{
	
	
}


void CDLL::ShowProperties()
{
	//CMyFrame *MyFrame = new CMyFrame(this);
	//MyFrame->ShowModal();
	//delete MyFrame;
	
}

void CDLL::CreateApiMenu(void) 
{

	NaviApiMenu = new CNaviApiMenu( GetMsg(MSG_MARKERS).wchar_str());	// nie u¿uwaæ delete - klasa zwalnia obiekt automatycznie
	NaviApiMenu->AddItem( GetMsg(MSG_NEW_MARKER).wchar_str(),this, MenuNew, true );
	//NaviApiMenu->AddItem( GetMsg(MSG_DELETE_MARKER).wchar_str(),this, MenuDelete, true );
	//NaviApiMenu->AddItem( GetMsg(MSG_MOVE_MARKER).wchar_str(),this, MenuMove, true );
	//NaviApiMenu->AddItem( GetMsg(MSG_PROPERTIES_MARKER).wchar_str(),this, MenuProperties, true );
	
}

void *CDLL::MenuConfig(void *NaviMapIOApiPtr, void *Input) 
{

	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Config();

	return NULL;
}

void *CDLL::MenuNew(void *NaviMapIOApiPtr, void *Input) 
{

	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_NEW);

	return NULL;
}

void *CDLL::MenuDelete(void *NaviMapIOApiPtr, void *Input) 
{

	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_DELETE);

	return NULL;
}

void *CDLL::MenuProperties(void *NaviMapIOApiPtr, void *Input)
{	
	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_PROPERTIES);
	
	return NULL;	
}

void *CDLL::MenuMove(void *NaviMapIOApiPtr, void *Input)
{	
	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Menu(BUTTON_TYPE_MOVE);
	
	return NULL;	
}

void CDLL::Menu(int type)
{
	
	if(SelectedPtr == NULL && type != BUTTON_TYPE_NEW)
	{
		wxMessageBox(GetMsg(MSG_SELECT_MARKER_FIRST));
		return;
	}
	
	
	switch(type)
	{
		case BUTTON_TYPE_NEW:
			New(MapX,MapY); // punkty na mapie
		break;

		case BUTTON_TYPE_DELETE:
			Delete(); // punkty na mapie
		break;

		case BUTTON_TYPE_PROPERTIES:
			ShowProperties();
		break;

		case BUTTON_TYPE_MOVE:
			Move();
		break;
	}
		
	GetBroker()->Refresh(GetBroker()->GetParentPtr());

}



void CDLL::Render(void)
{
		
	MapScale = Broker->GetMapScale();
	Angle = GetBroker()->GetAngle();
	SetMapScale(MapScale);
	SetValues();
		
	if(FirstTime)
	{
		CreateTextures();
		ReadConfig();
		FirstTime = false;
	}
	
	
	RenderMarkers();
	
	if(SelectedPtr != NULL)
		RenderSelection();

}

void CDLL::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockMarkerTGA_0;
	BlockMarkerTGA_0.Ptr = MemoryBlock;
	BlockMarkerTGA_0.Size = MemoryBlockSize;
	TextureMarkerTGA_0 = LoadFromMemoryBlockTGA( &BlockMarkerTGA_0 );

}

void CDLL::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CDLL::CreateTextures(void) 
{
	//wxMemoryInputStream memory(iconset,iconset_size);
	
	//wxString path = wxString::Format(_("%s%s"),GetWorkDir().wc_str(),_(MARKER_ICONSET_FILE_NAME));
	//if (!wxFileExists(path))
		//return;
	wxMemoryInputStream memory(icons,icons_size);
	
	wxZipInputStream zip(memory);
	wxZipEntry *entry;
	int i = 0;
	while((entry = zip.GetNextEntry()) != NULL)
	{
		wxString str = entry->GetName();
		unsigned char *buffer = (unsigned char*)malloc(zip.GetLength());
		int size = zip.GetLength();
		zip.Read( buffer,size );
		CreateSymbol(buffer, size);
		CreateTexture( TextureMarkerTGA_0,  &MarkerTextureID_0 ); // selected icon
		MarkerIcons->NewIcon(buffer, size, MarkerTextureID_0,i);
		i++;
	}
	
	//for(int i = 0; i < vPoints.size();i++)
   //	vPoints[i].texture_id = MarkerIcons->GetItem(vPoints[i].icon_id)->texture_id;


}

std::vector <SMarker> CDLL::GetPoints()
{
	return vPoints;
}

void *CDLL::MarkerGet(void *NaviMapIOApiPtr, void *Params)
{
	int id = (int)Params;
	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	return (void*)ThisPtr->Get(id);
}


SMarker *CDLL::Get(int id)
{
	return &vPoints[id];
}


void *CDLL::MarkerCount(void *NaviMapIOApiPtr, void *Params)
{
	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	return (void*)ThisPtr->Count();
}

int CDLL::Count()
{
	return vPoints.size();
}


void *CDLL::MarkerNew(void *NaviMapIOApiPtr, void *Params)
{
	SMarker *pt = (SMarker*)Params;
	CDLL *ThisPtr = (CDLL*)NaviMapIOApiPtr;
	ThisPtr->Add(pt->x,pt->y,pt->icon_id,pt->name,pt->description,pt->type);
		
	return NULL;
}


void CDLL::Add(double x, double y, int icon_id, wchar_t *name, wchar_t *description, int type = 0)
{
	SMarker Points;
	memset(&Points,0,sizeof(Points));
	Points.x = x;
	Points.y = y;
	Points.icon_id = MarkerIcons->GetItem(icon_id)->icon_id;
	Points.texture_id = MarkerIcons->GetItem(icon_id)->texture_id;
	Points.type = type;
	
		
	if(name != NULL)
		wcscpy_s(Points.name,MARKER_NAME_SIZE, name);
	
	if(description != NULL)
		wcscpy_s(Points.description,MARKER_DESCRIPTION_SIZE,description);
	
	//LastAdedMarker = &Points;	
	vPoints.push_back(Points);
}


void CDLL::New(double x, double y)
{
	
	wchar_t text[255];
	wsprintf(text,L"%s%d",GetMsg(MSG_MARKER).wc_str(),vPoints.size());
	Add(x,y,0,text,NULL);

}



void CDLL::AddField(wchar_t *name, wchar_t *value, SMarker *Marker )
{
	/*SFields *Fields = new SFields();
	Fields->next = NULL;
	wcscpy_s(Fields->name,64,name);
	wcscpy_s(Fields->value,64,value);
		
//	if(Marker->field == NULL)
//	{
	//	Marker->field = Fields;
		//return;	
	//}
	
	SFields *fld = Marker->field;
	while( fld->next != NULL)
		fld = fld->next;
	
	fld->next = Fields;
		*/
	
}

void CDLL::Delete()
{
	std::vector<SMarker>::iterator it;
	it = vPoints.begin();	
	while(it != vPoints.end())
	{
		if(SelectedPtr == &*it)
		{
			vPoints.erase(it);
			SelectedPtr = NULL;
			return;
		}
		
		it++;
	}
	
}
//void CDLL::Lock(double x , double y)
//{
/*	std::vector<SMarker>::iterator it;
	it = vPoints.begin();	
	while(it != vPoints.end())
	{
//		if(SelectedPtr == &*it && it->lock)
//		{
//			it->lock = false;
//			return;
//		}
		
		if(SelectedPtr == &*it && !it->lock)
		{	
			it->lock = true;
			return;
		}
		
		it++;
	}
	*/
//}

void CDLL::Move()
{
	if(SelectedPtr == NULL)
		return;
	
	SelectedPtr->x = MapX;
	SelectedPtr->y = MapY;
	GetBroker()->Refresh(GetBroker()->GetParentPtr());
	

}

// from NaviGeometry
bool CDLL::IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2) 
{
	if( ((px > bx1) && (px < bx2)) && ((py > by1) && (py < by2)) )
		return true;
	else
		return false;

}

void CDLL::SetMapScale(double scale)
{
	MapScale = scale;
}

// must be in render to set all values
void CDLL::SetValues()
{
	SetSmoothScaleFactor( MapScale );
	
	RectWidth = RECT_WIDTH / SmoothScaleFactor;
	RectHeight = RECT_HEIGHT / SmoothScaleFactor;
	TranslationX = (RECT_WIDTH /2)/SmoothScaleFactor; // point in red circle of texture
	TranslationY = (RECT_HEIGHT/2)/SmoothScaleFactor; // point in red circle of texture
	InfoHeight = INFO_HEIGHT/SmoothScaleFactor;
	InfoWidth = INFO_WIDTH/SmoothScaleFactor;
	HotSpotX = (RECT_WIDTH/2)/SmoothScaleFactor;
	HotSpotY = (RECT_HEIGHT/2)/SmoothScaleFactor;
	InfoMargin = INFO_MARGIN/SmoothScaleFactor;

	
}

void CDLL::RenderPoints()
{
	glPointSize(20);
			
	for(unsigned int i = 0; i < vPoints.size(); i++)
	{
		glPushMatrix();
		glTranslatef(vPoints[i].x,vPoints[i].y,0.0f);
		glBegin(GL_POINTS);
			glVertex2f(0.0f,0.0f); 
		glEnd();	
		glPopMatrix();
	}
	
}

void CDLL::RenderDistance()
{
	glLineWidth(3);
	glColor3f(1.0f,0.0f,0.0f);
		
	glBegin(GL_LINES);
			glVertex2f(SelectedPtr->x,SelectedPtr->y);
			glVertex2f(MapX ,MapY);			
	glEnd();
	
	glLineWidth(1);
}

void CDLL::RenderHotSpot()
{
	
}

void CDLL::	RenderSelection()
{
	
	
	glEnable(GL_TEXTURE_2D);		
	glEnable(GL_BLEND);
	
	double x,y;
	x = SelectedPtr->x; 
	y = SelectedPtr->y;
		
	//glBindTexture( GL_TEXTURE_2D, MarkerTextureID_0 );
	
	glPushMatrix();
		glTranslatef(x,y,0.0f);
		glDisable(GL_TEXTURE_2D);

	//hot spot
	//glColor4f(1.0f,1.0f,1.0f,1.0f);	
		//glPointSize(5);
		//glBegin(GL_POINTS);
			//glVertex2f(0.0,0.0);
		//glEnd();
	
	glPopMatrix();
		
	
	glPushMatrix();
	glTranslatef(x , y ,0.0f);
	
		//glEnable(GL_POINT_SMOOTH);
	// hot spot
		//glColor4f(1.0f,1.0f,1.0f,1.0f);	
		//glPointSize(5);
		//glBegin(GL_POINTS);
			//glVertex2f(0.0,0.0);
		//glEnd();
	
		glColor4f(1.0f,1.0f,1.0f,0.5f);	
		glBegin(GL_POLYGON);
			glVertex2f(-InfoWidth, -InfoHeight);
			glVertex2f(-InfoWidth , InfoHeight);
			glVertex2f(InfoWidth , InfoHeight);
			glVertex2f(InfoWidth, -InfoHeight);
		glEnd();
		
		//glColor4f(1.0f,1.0f,1.0f,0.5f);	
		//glBegin(GL_POLYGON);
			//glVertex2f(-InfoWidth + InfoMargin, -InfoHeight + InfoMargin);
			//glVertex2f(-InfoWidth + InfoMargin , InfoHeight + InfoMargin);
			//glVertex2f( InfoWidth + InfoMargin , InfoHeight + InfoMargin);
			//glVertex2f( InfoWidth + InfoMargin, -InfoHeight + InfoMargin);
		//glEnd();
	
	glPopMatrix();
	
	
	//char text[128];
	//double to_x, to_y;
	//GetBroker()->Project(x,y,&to_x,&to_y);
	//glColor4f(1.0f,1.0f,1.0f,1.0f);
		
	//float height = RenderText(x + TranslationX + InfoWidth , y , SelectedPtr->name);
	//sprintf(text,"%s %s",FormatLongitude(to_x).char_str(),FormatLatitude(-to_y).char_str());
	//height = RenderText(x + TranslationX + InfoWidth , y + height * 2, text);
			
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);

}

float CDLL::RenderText(double x, double y, wchar_t *text)
{
	if(MapScale < Factor)
		return 0;

	float width, height;
	width = (Font->GetWidth(text)/2)/SmoothScaleFactor;
	height = (Font->GetHeight()/2)/SmoothScaleFactor;
	Font->Render(x - width , y - height , text);
	
	return height;
}

float CDLL::RenderText(double x, double y, char *text)
{
	if(MapScale < Factor)
		return 0;
	
	float width = (Font->GetWidth(text)/2)/SmoothScaleFactor;
	float height = (Font->GetHeight()/2)/SmoothScaleFactor;
		
	Font->Render(x - width , y - height , text);

	return height;
}

void CDLL::RenderIcons()
{
	CMarkerIcons *icons = GetMarkerIcons();
	std::vector<SIcon*>::iterator it = icons->First();
	SIcon *ico;

	
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(SelectedPtr->x + RectWidth ,SelectedPtr->y + InfoHeight,0.0f);
	
	while (it != icons->Last())
	{
		ico = *it;
		glBindTexture( GL_TEXTURE_2D, ico->texture_id );
		
		glBegin(GL_QUADS);
			glColor4f(1.0,1.0,1.0,0.2);
			glVertex2d(TranslationX, -TranslationY);
			glVertex2d(TranslationX, TranslationY);
			glVertex2d(-TranslationX, TranslationY);
			glVertex2d(-TranslationX, -TranslationY);
		glEnd();
		
		glEnable(GL_TEXTURE_2D);
			glColor4f(1.0,1.0,1.0,1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,1.0f); glVertex2f( TranslationX,  -TranslationY);	
			glTexCoord2f(1.0f,0.0f); glVertex2f( TranslationX,  TranslationY);
			glTexCoord2f(0.0f,0.0f); glVertex2f(  -TranslationX,   TranslationY);
			glTexCoord2f(0.0f,1.0f); glVertex2f(  -TranslationX ,  -TranslationY);
		glEnd();
		glDisable(GL_TEXTURE_2D);		
		
		
		it++;

	}
	glDisable(GL_BLEND);
	glPopMatrix();
	
}

void CDLL::RenderMarkers()
{
	
	glEnable(GL_BLEND);	
	for(unsigned int i = 0; i < vPoints.size(); i++)
	{
		
		glEnable(GL_TEXTURE_2D);		
		
		glColor3f(1.0f,1.0f,1.0f);
		glPushMatrix();
		glTranslatef(vPoints[i].x,vPoints[i].y,0.0f);
		glRotatef(-Angle,0.0f,0.0f,1.0f);
		glBindTexture( GL_TEXTURE_2D, vPoints[i].texture_id );

		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,1.0f); glVertex2f( TranslationX,  -TranslationY);	
			glTexCoord2f(1.0f,0.0f); glVertex2f( TranslationX,  TranslationY);
			glTexCoord2f(0.0f,0.0f); glVertex2f(  -TranslationX,   TranslationY);
			glTexCoord2f(0.0f,1.0f); glVertex2f(  -TranslationX ,  -TranslationY);
		glEnd();

		
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
		RenderText(vPoints[i].x , vPoints[i].y + RectWidth , vPoints[i].name);
	}
	glDisable(GL_BLEND);
	
	
}

bool CDLL::GetClickedOnButton()
{
	return ClickedOnButton;

}

void CDLL::SetClickedOnButton(bool value)
{
	ClickedOnButton = value;
}

void CDLL::SetMouseXY(int x, int y)
{
	MouseX = x;
	MouseY = y;
}

void CDLL::RenderMouseSelection()
{
	glPushMatrix();
	glTranslatef(MouseX,MouseY,0.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();
}

void CDLL::SetErrorCode(int er)
{
	ErrorCode = er;
}

int CDLL::GetErrorCode()
{
	return ErrorCode;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
//
// info window do menu i info boxa
//
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 


BEGIN_EVENT_TABLE(CMyInfo,wxDialog)
	EVT_CONTEXT_MENU(CMyInfo::OnContextMenu)
	EVT_MENU(123,CMyInfo::On123)
	//EVT_PAINT
END_EVENT_TABLE()


CMyInfo::CMyInfo(CDLL *Parent)
:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER )
{
	m_DLL = Parent;

	this->SetForegroundColour(*wxRED);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);
	wxButton *ButtonClose = new wxButton(this,wxID_ANY,_("Close"),wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(ButtonClose,0,wxALL,5);
		
	wxStaticText *labellon = new wxStaticText(this,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(labellon,0,wxALL,5);

	textlon = new wxStaticText(this,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	TopSizer->Add(textlon,0,wxALL,5);
	
	wxStaticText *labellat = new wxStaticText(this,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(labellat,0,wxALL,5);
	
	textlat = new wxStaticText(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	TopSizer->Add(textlat,0,wxALL,5);

	this->SetSizer(TopSizer);

	this->SetBackgroundColour(wxColor(255,255,255));
	this->SetTransparent(200);
	
	
}

CMyInfo::~CMyInfo()
{
}



//void CMyInfo::OnPaint(wxPaintEvent &event)
//{
	//wxWindowDC *dc;
	//dc.
//}

void CMyInfo::ShowPopupMenu()
{	
	wxMenu *menu  = new wxMenu();
	menu->Append(123,_("abc"));
	PopupMenu(menu);
		
}

void CMyInfo::ShowWindow(bool show)
{
	if(show)
	{
		double to_x, to_y;
		SMarker *MarkerSelectedPtr = m_DLL->GetSelectedPtr();
		m_DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
		textlon->SetLabel(FormatLongitude(to_x));
		textlat->SetLabel(FormatLongitude(-to_y));
	}
	
	Show(show);
}

void CMyInfo::OnContextMenu(wxContextMenuEvent &event)
{
	//delete menu;
}

void CMyInfo::On123(wxCommandEvent &event)
{
	//CDLL *dll = m_DLL;
	m_DLL->Delete();
	//wxMessageBox(_("aaa"));
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
//
// ikony markera
//
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 

CMarkerIcons::CMarkerIcons()
{
	vIcons.clear();
}

CMarkerIcons::~CMarkerIcons()
{

}

void CMarkerIcons::NewIcon(unsigned char *data, int size, int texture_id, int icon_id)
{
	SIcon *Icon = (SIcon*)malloc(size);
	Icon->icon = data;
	Icon->icon_size = size;
	Icon->texture_id = texture_id;
	Icon->icon_id = icon_id;
	vIcons.push_back(Icon);
}

std::vector<SIcon*>::iterator CMarkerIcons::First()
{
	return vIcons.begin();
}

SIcon* CMarkerIcons::GetItem(int id)
{
	if(id >= vIcons.size())
		return NULL;
	else
		return vIcons[id];
}

std::vector<SIcon*>::iterator CMarkerIcons::Last()
{
	return vIcons.end();
}

size_t CMarkerIcons::Count()
{
	return vIcons.size();
}


/*
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	SetDisplayID(NDS_MARKER);
	Notebook = NULL;
	MarkerSelectedPtr = NULL;
}

CDisplayPlugin::~CDisplayPlugin()
{

}

bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) 
{
	return false;
}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	//Refresh();
	//wxMilliSleep(50);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{

	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}
void CDisplayPlugin::OnRender(wxGCDC &dc)
{
	DrawMarkerData(dc);
} 

void CDisplayPlugin::DrawMarkerData(wxGCDC &dc)
{
	
	MarkerSelectedPtr = DLL->GetSelectedPtr();

	if(MarkerSelectedPtr == NULL)
		return; 
	
		
	double to_x, to_y;
	DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
		
	SIcon *Icon =  DLL->GetMarkerIcon(MarkerSelectedPtr->icon_id);
	if(Icon == NULL)
		Icon =  DLL->GetMarkerIcon(MARKER_DEFAULT_ICON_ID);
	
	wxMemoryInputStream in_0((const unsigned char*)Icon->icon, Icon->icon_size);
	wxImage img_0(in_0,wxBITMAP_TYPE_ANY);
	wxBitmap bmp_0(img_0);
	
	dc.DrawBitmap(bmp_0,0,0,false);
	
	


}
*/
////////////////////////////////////////////////////////////////////////////
void NAVIMAPAPI *CreateNaviClassInstance(CNaviBroker *NaviBroker) 
{
	CDLL *DLL = new CDLL(NaviBroker);
	return (void*) ( DLL );

}

const NAVIMAPAPI wchar_t *NaviPluginIntroduce(int LangID) 
{
	SetLangId(LangID);
	return TEXT("Markers");	
}

int NAVIMAPAPI GetNaviPluginType(void) 
{
	return MAP_PLUGIN_RUN_ON_DEMAND;
}

#if defined(_WIN32) || defined(_WIN64)
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return 1;
}
#endif

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete ptr;
}
////////////////////////////////////////////////////////////////////////////
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
//const wchar_t *NaviDisplayIntroduce(int LanguageID) {
//
//	switch( LanguageID ) 
//	{
//		case 0: 
//			return L"Marker";
//			break;
//
//		default:
//			return L"Marker";
//	};
//	
//	return L"Marker";
//};
//
//const int NaviDisplayID()
//{
//	return NDS_MARKER;
//}
//
//CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID) 
//{
//	
//	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
//	return SimplePlugin;
//};
