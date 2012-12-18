#include "conf.h"
#include "dll.h"
#include "frame.h"
#include "tools.h"
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include "icons.h"

#define BUFSIZE 512

//CNaviBroker *BrokerPtr;
//CNaviMapIOApi *ThisPtr;


unsigned char PluginInfoBlock[] = {
0x39,0x0,0x0,0x0,0x57,0x38,0x37,0x98,0x0,0xc8,0xc7,0xab,0x11,0x2e,0xfd,0xb7,0x8a,0xc,0x72,0xd2,0x4b,0x91,0x24,0x99,0x1,0x52,0xf9,0x7,0xaf,0xaa,0xa8,0x1,0xb3,0x7f,
0x16,0x78,0x3e,0xd9,0xc9,0x42,0x78,0x14,0x6d,0xe6,0xdb,0xda,0xf4,0xe0,0x75,0x4c,0xec,0x1b,0x7a,0x43,0xf0,0xc5,0x98,0x5b,0x2d,0x2a,0x19,0x4c,0xa5,0x91,0xe6,0x4c,0x96,0xf2,
0x37,0x5e,0x2,0xdb,0xcd,0xb8,0x7c,0x10,0xd1,0x9f,0xa4,0x2a,0x4f,0xd4,0x97,0x82,0xe2,0x37,0x97,0x17,0x3,0x92,0xb1,0xf6,0x7c,0xf6,0x71,0x6c,0x43,0xa3,0x11,0x5d,0xd0,0xfe,
0x56,0xbe,0x96,0xcd,0xec,0x9a,0xbd,0xf4,0xf4,0x3e,0x81,0xd7,0xa0,0xc1,0xa1,0x2a,0xf0,0x26,0x4d,0x6b,0x62,0x6,0x9,0xcb,0x60,0x62,0x8,0xd0,0xee,0x93,0x1a,0x14,0x38,0xa7,
0x7b,0xfb,0x7e,0x3f,0x21,0x1f,0x6c,0x19,0x3e,0xe0,0xe8,0x8,0x24,0xef,0x8a,0x9b,0xde,0x51,0x7c,0x52,0x55,0x7d,0xbe,0x16,0xd3,0x47,0x85,0xb,0x99,0xdb,0x71,0x19,0x99,0xe8,
0x10,0xbb,0x83,0xc0,0x10,0x85,0x2,0x18,0x0,0x17,0x84,0xc7,0x11,0x2f,0xa1,0xd,0x1d,0x88,0x2c,0x58,0xe,0x98,0x71,0x3,0x47,0xf,0x29,0x1a,0x98,0xa1,0xe0,0x72,0xbf,0xc4,
0x0,0x37,0x97,0x62,0xc3,0x0,0x65,0xd9,0x7a,0x97,0x3,0x87,0x19,0x4,0x2d,0xf3,0x9f,0x98,0xbc,0xf2,0x5c,0xa2,0xa1,0x44,0x85,0x10,0x22,0x11,0xa9,0xba,0x6a,0x11,0x8f,0x8a,
0x38,0x3e,0x1e,0x74,0xe2,0x6b,0x95,0xea,0xec,0xb9,0x34,0x7,0x8f,0x7e,0x5c,0xc5,0x14,0xfd,0x86,0x70,0x7e,0xb6,0x98,0x64,0x4c,0x53,0x96,0x77,0x26,0x6c,0x8e,0x84,0x51,0x51,
0x12,0x45,0x7b,0x55,0x8c,0xc,0x1c,0x9a,0xd4,0x9,0xd1,0x1d,0x14,0x45,0x0,0xab,0xd6,0x11,0xa0,0x3d,0x1b,0x9b,0x77,0xed,0xfb,0x36,0x9,0x56,0xe6,0x23,0x63,0xbb,0x9a,0x6,
0x34,0xce,0x86,0xbd,0x67,0x44,0xd0,0xdc,0x7d,0x45,0x2a,0xf9,0x42,0x18,0xf8,0x90,0xd1,0x9,0x68,0x4b,0x74,0x45,0x7a,0x54,0xaf,0x97,0xaf,0x3,0x51,0x50,0x54,0xd2,0x81,0x7a,
0x2a,0x84,0xf1,0x7d,0x9a,0x1e,0xfd,0x24,0xa9,0x37,0xf1,0x61,0xaf,0xdf,0x74,0x72,0x4c,0xf6,0xb9,0x78,0x1f,0x75,0x54,0x62,0x28,0xe2,0x73,0xf6,0xb6,0xd,0xc4,0x36,0xf5,0x28,
0xc6,0x4f,0x93,0x2a,0x53,0x59,0xf0,0xd,0xde,0x7f,0x73,0x7,0xa0,0x8b,0x98,0xae,0xd7,0x79,0x5c,0x64,0x77,0xcb,0x2d,0x11,0x3,0x36,0xd6,0xb0,0x82,0x8a,0x76,0x79,0x16,0x84,
0xe7,0x56,0x7d,0x54,0x7a,0x4b,0x2b,0x57,0xe,0x68,0x95,0x12,0x1e,0xcc,0xaf,0xb6,0x9e,0x7b,0xc5,0xa2,0x45,0x8e,0x98,0xf3,0x1,0x5c,0xee,0xd2,0x11,0x27,0x66,0x7f,0xa0,0x35,
0xf4,0xf0,0x9f,0x59,0xfc,0x94,0x34,0x92,0xe3,0xd6,0xd4,0x39,0xdc,0x69,0xcd,0x7f,0xa4,0x5c,0x9c,0x44,0x4f,0x64,0xd7,0x67,0x18,0x93,0x5c,0x6,0xed,0xcb,0x96,0xb7,0x5d,0x9d,
0x41,0x3f,0xd,0x33,0x8,0x31,0x3d,0x5,0x5c,0x9f,0x69,0x72,0x9e,0x81,0x79,0xcc,0x35,0x3e,0xe,0xf6,0x29,0xfb,0x97,0xa6,0x4e,0x7b,0x7e,0xe2,0x5,0x7b,0xaf,0xc4,0x87,0x2a,
0xb,0xe0,0xdc,0x0,0x18,0xb2};



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
			
			while(!_file.Eof())
			{	
				SMarker *buffer = (SMarker*)malloc(sizeof(SMarker));
				memset(buffer,0,sizeof(SMarker));
				_file.Read(buffer,sizeof(SMarker));
				Add(buffer->x,buffer->y,buffer->icon_id, buffer->name,buffer->description,buffer->type);
				free(buffer);
			}
		
			_file.Close();
		}
	}
}

void CDLL::ReadHeader()
{
	SMarkerHeader *header = (SMarkerHeader*)malloc(sizeof(SMarkerHeader));
	_file.Read(header,sizeof(SMarkerHeader));
	free(header);
}

void CDLL::WriteConfig()
{
	FileConfig->Write(_(KEY_FILEPATH), FilePath);
	
	if(_file.Open(PointsPath,wxFile::write))
	{
		WriteHeader();
		
		
		for(unsigned int i = 0; i < vPoints.size();i++)
			_file.Write(vPoints[i],sizeof(SMarker));

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
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
//	ThisPtr = (CNaviMapIOApi*)this;

}

void CDLL::Kill(void)
{
	NeedExit = true;
	delete MyInfo;
	delete MyFrame;
	WriteConfig();

	for(size_t i = 0; i < vPoints.size(); i++)
		free(vPoints[i]);

	vPoints.clear();
	
};

bool CDLL::GetNeedExit(void) 
{
	return NeedExit;
};

wxArrayString *CDLL::GetDataArray()
{
	return &DataArray;
};

void CDLL::Config()
{

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
	
	std::vector<SMarker*>::iterator it;
	it = vPoints.begin();
	
	while(it != vPoints.end())
	{
		if(IsPointInsideBox(MapX, MapY, (*it)->x - TranslationX, (*it)->y - TranslationY, (*it)->x + RectWidth-TranslationX , (*it)->y + RectHeight-TranslationY))
		{
			SelectedPtr =  *it;
			return;
		}
		
		it++;
	}

	ShowFrameWindow(false);
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
	std::vector<SMarker*>::iterator it;
	it = vPoints.begin();
	
	while(it != vPoints.end())
	{
		if(IsPointInsideBox(MapX, MapY, (*it)->x - TranslationX, (*it)->y - TranslationY, (*it)->x + RectWidth-TranslationX , (*it)->y + RectHeight-TranslationY))
		{
			SelectedPtr =  *it;
			ShowFrameWindow(true);
			return;
		}
		
		it++;
	}
	SelectedPtr = NULL;
	
}


void CDLL::ShowProperties()
{
	ShowFrameWindow(true);
}

void CDLL::CreateApiMenu(void) 
{

	NaviApiMenu = new CNaviApiMenu( GetMsg(MSG_MARKERS).wchar_str());	// nie u�uwa� delete - klasa zwalnia obiekt automatycznie
	NaviApiMenu->AddItem( GetMsg(MSG_NEW_MARKER).wchar_str(),this, MenuNew, true );
	NaviApiMenu->AddItem( GetMsg(MSG_DELETE_MARKER).wchar_str(),this, MenuDelete, true );
	//NaviApiMenu->AddItem( GetMsg(MSG_MOVE_MARKER).wchar_str(),this, MenuMove, true );
	NaviApiMenu->AddItem( GetMsg(MSG_PROPERTIES_MARKER).wchar_str(),this, MenuProperties, true );
	
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

}

std::vector <SMarker*> CDLL::GetPoints()
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
	return vPoints[id];
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
	SMarker *Points = (SMarker*)malloc(sizeof(SMarker));
	memset(Points,0,sizeof(SMarker));
	Points->x = x;
	Points->y = y;
	Points->icon_id = MarkerIcons->GetItem(icon_id)->icon_id;
	Points->texture_id = MarkerIcons->GetItem(icon_id)->texture_id;
	Points->type = type;
	
		
	if(name != NULL)
		wcscpy_s(Points->name,MARKER_NAME_SIZE, name);
	
	if(description != NULL)
		wcscpy_s(Points->description,MARKER_DESCRIPTION_SIZE,description);
	
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
	std::vector<SMarker*>::iterator it;
	it = vPoints.begin();	
	while(it != vPoints.end())
	{
		if(SelectedPtr == *it)
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
		glTranslatef(vPoints[i]->x,vPoints[i]->y,0.0f);
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
	float width, height;
	width = (Font->GetWidth(text)/2)/SmoothScaleFactor;
	height = (Font->GetHeight()/2)/SmoothScaleFactor;
		
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
		glTranslatef(vPoints[i]->x,vPoints[i]->y,0.0f);
		glRotatef(-Angle,0.0f,0.0f,1.0f);
		glBindTexture( GL_TEXTURE_2D, vPoints[i]->texture_id );

		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,1.0f); glVertex2f( TranslationX,  -TranslationY);	
			glTexCoord2f(1.0f,0.0f); glVertex2f( TranslationX,  TranslationY);
			glTexCoord2f(0.0f,0.0f); glVertex2f(  -TranslationX,   TranslationY);
			glTexCoord2f(0.0f,1.0f); glVertex2f(  -TranslationX ,  -TranslationY);
		glEnd();

		
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
		RenderText(vPoints[i]->x , vPoints[i]->y + RectWidth , vPoints[i]->name);
	}
	glDisable(GL_BLEND);
	
	
}

void CDLL::Render(void)
{
	
	MapScale = Broker->GetMapScale();
	Angle = GetBroker()->GetAngle();
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
	for(size_t i = 0; i < vIcons.size(); i++)
	{
		free(vIcons[i]->icon);
		free(vIcons[i]);
	}
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

unsigned char *GetNaviPluginInfoBlock()
{
	return PluginInfoBlock;
}

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CDLL*)ptr;
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
