#include <stdio.h>
#include <wx/wx.h>
#include "tools.h"
#define CONVERTED_DEGREE_LENGTH	15

int GlobalLanguageID;
const wxChar *nvLanguage[2][14] = 
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
	/*13*/	_("Change Icon")
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