#ifndef __CONF
#define __CONF
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#define DIR_SEPARATOR "\\"
#endif

#if defined(_LINUX32) || defined(_LINUX64)
#define DIR_SEPARATOR "/"
#endif

#define DIR_WORKDIR "workdir"
#define MARKER_CONFIG_FILE "marker.conf"
#define MARKER_DATA_FILE "marker.data"
#define MARKER_ICONSET_FILE_NAME "marker.icons"

#define PRODUCT_NAME "Markers"
#define PRODUCT_VERSION "0.1"
#define PRODUCT_COPYRIGHT "Copyright© 2010/2011 by NavSim. All rights reserved"


#define BUTTON_TYPE_ANY -1
#define BUTTON_TYPE_NEW 0
#define BUTTON_TYPE_DELETE 1
#define BUTTON_TYPE_PROPERTIES 2
#define BUTTON_TYPE_MOVE 3

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

#define INFO_WIDTH 32
#define INFO_HEIGHT 32
#define INFO_MARGIN 2

#define DEFAULT_FACTOR 50.0
#define FONT_SIZE 14


#define KEY_FILEPATH "FileName"
#define PARSER_SEPARATOR ","


#if defined(_LINUX32) || defined(_LINUX64)
	#define FONT_NAME "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define FONT_NAME "c:\\windows\\fonts\\Arial.ttf"
#endif

#define PLUGIN_ID 4
#define MARKER_HEADER_VERSION 1

#define MARKER_NAME_SIZE 32
#define MARKER_DESCRIPTION_SIZE 255
#define MARKER_DEFAULT_ICON_ID 0



// Languages
// . . . . . . . . . . . . . . . .
#define MSG_MARKER				0
#define MSG_MARKERS				1
#define MSG_NEW_MARKER			2
#define MSG_DELETE_MARKER		3	
#define MSG_MOVE_MARKER			4
#define MSG_PROPERTIES_MARKER	5
#define MSG_SELECT_MARKER_FIRST 6
#define MSG_NAME				7
#define MSG_DESCRIPTION			8
#define MSG_LONGITUDE			9
#define MSG_LATITUDE			10
#define MSG_ICON				11
#define MSG_CLOSE				12
#define MSG_CHANGE_ICON			13
//. . . . . . . . . . . . . . . . .

#define NV_PI 3.1415926535897932384626433
enum nvDistanceUnits { nvDefault, nvKilometer, nvNauticMiles, nvMeter };

typedef struct
{
	int version;

}SMarkerHeader;


typedef struct Fields
{
	wchar_t name[64 + 1];
	wchar_t value[64 + 1];
	struct Fields *next;

} SFields;

typedef struct Marker
{
	float x;
	float y;
	wchar_t name[MARKER_NAME_SIZE + 1];
	wchar_t description[MARKER_DESCRIPTION_SIZE + 1];
	int icon_id;
	int texture_id;
	int type;
	
}SMarker;

typedef struct
{
	int icon_id;
	int texture_id;
	unsigned char *icon;
	int icon_size;

} SIcon;

#endif