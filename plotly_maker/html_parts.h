#ifndef HTML_PARTS_H
#define HTML_PARTS_H

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
enum ARGS_INDEX {
  VALUES,     //1
  COLOR_MAP,  //2
  MATRIX_TYPE,//3
  TITLE,      //4
  TITLE_X,    //5
  TITLE_Y     //6
};
const int MAX_ELEMENT = 6;
extern const char kHtmlModel[];
extern const char kColorMapDefaultPart[];
extern const char kColorMapSunnyPart[];
extern const char kColorMapGlamourPart[];
extern const char kColorMapThermalPart[];
extern const char kColorMapGrayscalePart[];
extern const char kHeatMapTypePart[];
extern const char kSurfaceTypePart[];
//#STOP_GRAB_TO_DVS_NAMESPACE
}

#endif // HTML_PARTS_H
