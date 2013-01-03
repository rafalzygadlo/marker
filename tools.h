#ifndef __TOOLS_H
#define __TOOLS_H

#include <wx/wx.h>


wxString GetMsg(int id);
void SetLangId(int id);
wxString ConvertDegree(float degree); 
wxString FormatLongitude(float x); 
wxString FormatLatitude(float y);
double nvDistance(double lon1, double lat1, double lon2, double lat2, nvDistanceUnits distanceunit);
void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2);
double nvToRad( double degree ); 


#endif

