#include <stdio.h>
#include <wx/wx.h>
#include "conf.h"
#include "tools.h"
#define CONVERTED_DEGREE_LENGTH	15

int GlobalLanguageID;
const wxChar *nvLanguage[2][19] = 
{ 
	//en
	{
		_("Marker"),
		_("Markers"),
		_("Marker NEW"),
		_("Marker DELETE"),
		_("Marker MOVE Here"),
		_("Marker PROPERTIES"),
		_("Select marker first"), 
		_("Name"),
		_("Description"),
		_("Longitude"),
		_("Latitude"),
		_("Icon"),
		_("Close"),
		_("Change Icon"),
		_("Marker SETTINGS"),
		_("Distance unit"),
		_("Ok"),
		_("Cancel"),
		_("Click on Chart to put your marker")
	},
	//pl
	{
		_("Marker"),
		_("Markery"),
		_("Dodaj Marker"),
		_("Usu� Marker"),
		_("Przesu� Marker tutaj"),
		_("Ustawienia Markera"),
		_("Zaznacz najpierw marker"),
	    _("Nazwa"),
		_("Opis"),
		_("Longitude"),
		_("Latitude"),
		_("Ikona"),
		_("Zamknij"),
		_("Zmie� ikon�")
	}

};

const wxChar *nvDistanceN[2][3] = 
{ 
	//en
	{
		_("Nautic Miles"),
		_("Kilometer"),
		_("Meter"),
	},

	//pl
	{
		_("Mile morskie"),
		_("Kilometry"),
		_("Metry"),
	}

};


const wxChar *nvDistanceU[2][3] = 
{ 
	//en
	{
		_("NM"),
		_("km"),
		_("m"),
	},

	//pl
	{
		_("NM"),
		_("km"),
		_("m"),
	}

};

wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}
wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}


wxString GetDistanceName(size_t id)
{
	return nvDistanceN[GlobalLanguageID][id];
}

wxString GetDistanceUnit(size_t id)
{
	return nvDistanceU[GlobalLanguageID][id];
}

wxString GetMsg(int id)
{
	return nvLanguage[GlobalLanguageID][id];
}
void SetLangId(int id)
{
	GlobalLanguageID = id;
}
//degree = 40.044658660888672
wxString ConvertDegree(double degree) 
{
	int decimal = (int)degree;
    double minutes = (double)(degree - decimal) * 60;
    double second = (double)(minutes - (int)(minutes)) * 60;
	return wxString::Format(_("%02d� %02d' %02d''"),decimal, (int)minutes, (int)second);
      
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

double nvDistance(double lon1, double lat1, double lon2, double lat2, int distanceunit) 
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
		case nvMeter : return R * c * 1000;
		default:
			return (R *c) / 1.852;
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
