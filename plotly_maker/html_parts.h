#ifndef HTML_PARTS_H
#define HTML_PARTS_H

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
enum ARGS_INDEX {
  ARG_VALUES,     //%1
  ARG_COLOR_MAP,  //%2
  ARG_MATRIX_TYPE,//%3
  ARG_TITLE,      //%4
  ARG_TITLE_X,    //%5
  ARG_TITLE_Y ,   //%6
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_SIZE
};
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
