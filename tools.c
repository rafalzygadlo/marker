#include "tools.h"
#include <stdio.h>
#include <string.h>

#define CONVERTED_DEGREE_LENGTH	15


wxString ConvertDegree(float degree) {

	//static char str[CONVERTED_DEGREE_LENGTH];      
	 // memset(str,0,CONVERTED_DEGREE_LENGTH);

      int decimal = (int)degree;
      float minutes = (float)(degree - decimal) * 60;
      float second = (float)(minutes - (int)(minutes)) * 60;
	  return wxString::Format(_("%02d° %02d'%02d"),decimal, (int)minutes, (int)second);
      //sprintf(str, "%02d° %02d'%02d", decimal, (int)minutes, (int)second);
      
};

wxString FormatLongitude(float x) {

    
      if (x > 0.0f) {
        if (x <= 180.0f)
			return wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
            return wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			return wxString::Format(_("%s E"), ConvertDegree(-x).wc_str());
        else
			return wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      //return str;
};



wxString FormatLatitude(float y) {

    static char str[CONVERTED_DEGREE_LENGTH];
	//memset(str,0,CONVERTED_DEGREE_LENGTH);

//	if( y == 0 )
//		return "";

    if (y > 0)
		return wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		return wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

//    return str;

}

