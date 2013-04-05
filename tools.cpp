#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"
#include "version.h"

#define CONVERTED_DEGREE_LENGTH	15

int GlobalLanguageID;
const wxChar *nvLanguage[2][19] = 
{ 
	//en
	{
		_("Marker"),
		_("Markers"),
		_("Marker New"),
		_("Marker Delete"),
		_("Marker Move Here"),
		_("Marker Properties"),
		_("Select marker first"), 
		_("Name"),
		_("Description"),
		_("Longitude"),
		_("Latitude"),
		_("Icon"),
		_("Close"),
		_("Change Icon"),
		_("Marker Settings"),
		_("Distance unit"),
		_("Ok"),
		_("Cancel"),
		_("Click on Chart to put your marker.\nWhen done click Ok to save or Cancel to remove marker.")
	},
	//pl
	{
		_("Marker"),
		_("Markery"),
		_("Dodaj Marker"),
		_("Usuñ Marker"),
		_("Przesuñ Marker tutaj"),
		_("Ustawienia Markera"),
		_("Zaznacz najpierw marker"),
	    _("Nazwa"),
		_("Opis"),
		_("Longitude"),
		_("Latitude"),
		_("Ikona"),
		_("Zamknij"),
		_("Zmieñ ikonê")
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

wxString GetConfigFile()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir().wc_str(),wxT(DIR_SEPARATOR),_(CONFIG_FILE));
}

wxString GetWorkDir()
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
	buffer.Printf(wxT("%s%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	delete Paths;
	return buffer;
}


wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(APPLICATION_VERSION_STR),_(PRODUCT_COPYRIGHT));
}
wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(APPLICATION_VERSION_STR));
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
wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    double minutes = (float)(degree - decimal) * 60;
    double second = (float)(minutes - (int)(minutes)) * 60;
	return wxString::Format(_("%02d° %02d' %02.2f''"),decimal, (int)minutes, second);
      
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

bool SetLat(char *text, float *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(dindicator != 'S' && dindicator != 'N')
		result = false;
		
	if(degree > 90 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;
	
	double y;
	double _min;

	if(result)
	{
		_min = min + ((float)sec/60);
		y = degree + ((float)_min/60);
				
		if(dindicator == 'N')
			*val = -y;
		else
			*val = y;
	
	}else{
			
		return false;
	}

	return true;
}

bool SetLon(char *text, float *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	
	if(dindicator != 'W' && dindicator != 'E')
		result = false;
		
	if(degree > 180 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;

	double x;
	double _min;
	
	if(result)
	{
		_min = min + ((float)sec/60);
		x = degree + ((float)_min/60);
				
		if(dindicator == 'W')
			*val = -x;
		else
			*val = x;
	
	}else{
	
		return false;
	}

	return true;
}
