#include <stdio.h>
#include <wx/wx.h>
#include "conf.h"
#include "tools.h"
#define CONVERTED_DEGREE_LENGTH	15

int GlobalLanguageID;
const wxChar *nvLanguage[2][15] = 
{ 
	/*EN*/
	{
	/*0*/	_("Marker"),
	/*1*/	_("Markers"),
	/*2*/	_("Marker New"),
	/*3*/	_("Marker Delete"),
	/*4*/	_("Move Marker Here"),
	/*5*/	_("Marker Properties"),
	/*6*/	_("Select marker first"), 
	/*7*/   _("Name"),
	/*8*/	_("Description"),
	/*9*/	_("Longitude"),
	/*10*/	_("Latitude"),
	/*11*/	_("Icon"),
	/*12*/	_("Close"),
	/*13*/	_("Change Icon"),
			_("Font %s not found in program folder.\nCopy font file to the program folder and start plugin again."),
	},
	/*PL*/
	{
	/*0*/	_("Marker"),
	/*1*/	_("Markery"),
	/*2*/	_("Dodaj Marker"),
	/*3*/	_("Usuñ Marker"),
	/*4*/	_("Przesuñ Marker tutaj"),
	/*5*/	_("Ustawienia Markera"),
	/*6*/	_("Zaznacz najpierw marker"),
	/*7*/   _("Nazwa"),
	/*8*/	_("Opis"),
	/*9*/	_("Longitude"),
	/*10*/	_("Latitude"),
	/*11*/	_("Ikona"),
	/*12*/	_("Zamknij"),
	/*13*/	_("Zmieñ ikonê")
	}

};


wxString GetMsg(int id)
{
	return nvLanguage[GlobalLanguageID][id];
}
void SetLangId(int id)
{
	GlobalLanguageID = id;
}

wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    float minutes = (float)(degree - decimal) * 60;
    float second = (float)(minutes - (int)(minutes)) * 60;
	return wxString::Format(_("%02d° %02d'%02d"),decimal, (int)minutes, (int)second);
      
}

wxString FormatLongitude(float x) 
{
      wxString str;

      if (x > 0.0f) {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      return str;
}



wxString FormatLatitude(float y) 
{
	
	wxString str;

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

    return str;

}

double nvDistance(double lon1, double lat1, double lon2, double lat2, nvDistanceUnits distanceunit) 
{

	double dLat = nvToRad( lat2 - lat1 );
	double dLon = nvToRad( lon2 - lon1 );
	double R = 6371.0;

	double a = ( sin(dLat/2) * sin(dLat/2) )  +  ( cos( nvToRad(lat1) ) * cos( nvToRad(lat2) ) * sin(dLon/2) * sin(dLon/2) );
	double c = 2 * atan2( sqrt(a), sqrt( 1 - a ) );

	switch( distanceunit ) 
	{
		case nvKilometer: return R * c;
		case nvNauticMiles: return (R *c) / 1.852;
		default:
			return c;
	}
}

void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2)
{
	*v1 = (lon1 + lon2) / 2;
	*v2 = (lat1 + lat2) / 2;
}

double nvToRad( double degree ) 
{
	return (NV_PI * degree / 180 );
}

void nvPointOfIntersection(double a1, double b1,double a2, double b2, double *x, double *y)
{
	*x = (b1 - b2)/(a2 - a1);
	*y = (a2 * b1 - b2 * a1) / (a2 - a1); 
}
