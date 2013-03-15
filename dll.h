#ifndef __DLL
#define __DLL
#include "NaviMapIOApi.h"
#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/notebook.h>
#include "tgamem.h"
#include <GL/gl.h>
#include "NaviFont.h"
#include "NaviDisplayApi.h"
#include "conf.h"
#include "positiondialog.h"

#ifdef _WIN32
	#include <windows.h>
#endif

class CDataThread;
class CMarkerIcons;
class CMyFrame;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
//DLL
class CPositionDialog;
class CDLL :public CNaviMapIOApi
{	
	double CenterX, CenterY;
	wxArrayPtrVoid TextureList;
	CPositionDialog *PositionDialog;
	CMyFrame *MyFrame;
	bool ShowWindow;
	double HotSpotX;
	double HotSpotY;
	int SelectedTextureID;
	int SelectedIconID;
	SMarker *NewPtr;
	CMarkerIcons *MarkerIcons;
	wxFile _file;
	float Angle;
	double Factor;
	bool MoveMarker;
	double MOM_X, MOM_Y;
	SMarker *SelectedPtr, *HighlightedPtr;
	int ErrorCode;
	double SmoothScaleFactor;
	bool NeedExit;
	bool IsData;
	double MapScale;
	bool FirstTime;
	int ButtonAction;
	double MapX,MapY;
	CDataThread *DataThread;
	bool FirstRun;
	wxString FilePath;
	wxFileConfig *FileConfig;
	wxString ConfigPath;		
	CNaviBroker *Broker;
	wxArrayString DataArray;
	wxString PointsPath;
	std::vector <SMarker*> vPoints;
	std::vector <SMarker*> vDistance;
	int MouseX,MouseY;
	int Type;
	double RectWidth;
	double RectHeight;
	double InfoWidth, InfoHeight;
	double InfoMargin;
	double TranslationX, TranslationY;
	bool ClickedOnButton;
	TTexture *TextureMarkerTGA_0, *TextureMarkerTGA_1, *TextureMarkerTGA_2, *TextureMarkerTGA_3, *TextureMarkerTGA_4, *TextureMarkerTGA_5;
	GLuint MarkerTextureID_0, MarkerTextureID_1, MarkerTextureID_2, MarkerTextureID_3, MarkerTextureID_4, MarkerTextureID_5;
	bool DBLClick;
	//CNaviPixmapFont *Font;
	double MarkerX,MarkerY;
	double VisibleMap[4];
	bool FromLMB;
	int DistanceUnit;

	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateApiMenu(void);
	void SetButtonAction(int action);
	void Menu(int type);
	wxString GetWorkDir(void);
	void WritecConfig();
	void ReadConfig();
	void CreateTextures(void);
	void WriteConfig();
	std::vector <SMarker*> GetPoints();
	void SetMouseXY(int x, int y);
	void SetMapScale(double scale);
	void SetClickedOnButton(bool value);
	int GetType();
	void SetMOM(double x, double y);
	bool GetClickedOnButton();
	void Add(double x, double y, int icon_id, wchar_t *name, wchar_t *description, int type = 0, bool _new = false);
	
	void New(double x, double y);	
	void RenderIcons();
	void RenderPoints();
	void RenderMarkers();
	void RenderSelected();
	void RenderHighlighted();
	void RenderHotSpot();
	void RenderMouseSelection();
	void RenderButton(float x1, float y1, float x2, float y2, bool selected);
	void RenderText(double x, double y, wchar_t *text);
	bool IsPointInsideBox(double px, double py, double bx1, double by1, double bx2, double by2); 
	void RenderMenu(float x , float y);
	void RenderPositionMarker(double x, double y);
	void RenderDistance();
	void SetValues();
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void SetSmoothScaleFactor(double _Scale);
	void ShowProperties();
	void ShowInfo(int x, int y);
	void HideInfo();
	void Move();
	void ReadHeader();
	void WriteHeader();
	int Count();
	SMarker *Get(int id);
	double Distance();
	SMarker* SetMarker(double x, double y);
	void SetPosition(double x, double y);
	void RenderNew();
	
	static void *MenuConfig(void *NaviMapIOApiPtr, void *Input);
	static void *MenuNew(void *NaviMapIOApiPtr, void *Input);
	static void *MenuDelete(void *NaviMapIOApiPtr, void *Input);
	static void *MenuProperties(void *NaviMapIOApiPtr, void *Input);
	static void *MenuMove(void *NaviMapIOApiPtr, void *Input);
	static void *MenuSettings(void *NaviMapIOApiPtr, void *Input);
				
public:
	
	CDLL(CNaviBroker *NaviBroker);
	~CDLL();
	

	CNaviBroker *GetBroker();
	void Delete();
	bool GetNeedExit(void);
	wxString GetFilePath();
	wxArrayString *GetDataArray();
	int GetErrorCode();
	SMarker *GetSelectedPtr();
	CMarkerIcons *GetMarkerIcons();
	size_t GetMarkerIconsCount();
	SIcon *GetMarkerIcon(int id);
	void AddField(wchar_t *name, wchar_t *value, SMarker *Marker);
	void SetErrorCode(int er);
	void SetFilePath(wxString file);
	void SetMarkerTextureID(int id);
	void SetMarkerIconID(int id);
	void ShowPopupMenu(bool show);
	void ShowFrameWindow(bool show);
	SMarker *GetNewMarkerPtr();
	void Append();
	void Remove();
	
	virtual void Run(void *Params); 
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
	
	static void *MarkerNew(void *NaviMapIOApiPtr, void *Params);
	static void *MarkerCount(void *NaviMapIOApiPtr, void *Params);
	static void *MarkerGet(void *NaviMapIOApiPtr, void *Params);
		
};

class CMarkerIcons
{

	
	std::vector<SIcon*> vIcons;
	
public:
	
	CMarkerIcons();
	~CMarkerIcons();
	void NewIcon(unsigned char *data, int size, int texture_id, int icon_id);
	std::vector<SIcon*>::iterator First();
	std::vector<SIcon*>::iterator Last();
	size_t Count();
	SIcon *GetItem(int id);
	
};

#endif 
