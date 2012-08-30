#ifndef __TOOLS_H
#define __TOOLS_H

#include <wx/wx.h>


wxString GetMsg(int id);
void SetLangId(int id);
wxString ConvertDegree(float degree); 
wxString FormatLongitude(float x); 
wxString FormatLatitude(float y);


#endif

