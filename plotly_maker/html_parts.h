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
  ARG_TITLE_Y,    //%6
  ARG_TITLE_Z,    //%7
  ARG_JS_VER,     //%8
  ARG_ASPECT_RATIO_WIDTH,     //%9
  ARG_ASPECT_RATIO_HEIGHT,     //%10
  ARG_ASPECT_WIDTH_OR_HEIGHT, //11 "width" if ARG_ASPECT_RATIO_WIDTH > ARG_ASPECT_RATIO_HEIGHT and "height" if not
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_SIZE
};

enum ARGS_WARNING_PAGE_INDEX {
  ARG_WORKING_FOLDER,
  ARG_JS_VERSION,
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_WARNING_PAGE_SIZE
};


enum ARGS_REPORT_PAGE_INDEX {
  ARG_REPORT_TITLE,       //%1
  ARG_SVG_ICON,           //%2
  ARG_REPORT_DESCRIPTION, //%3
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_REPORT_PAGE_SIZE
};

enum ARGS_DATE_TIME_PAGE_INDEX {
  ARG_JS_NAME,            //%1
  ARG_DATE_TIME_VALUES,   //%2
  ARG_Y_DATE_TIME_VALUES, //%3
  ARG_DATE_TIME_ASPECT_RATIO_WIDTH,     //%4
  ARG_DATE_TIME_ASPECT_RATIO_HEIGHT,     //%5
  ARG_DATE_TIME_ASPECT_WIDTH_OR_HEIGHT, //%6 "width" if ARG_ASPECT_RATIO_WIDTH > ARG_ASPECT_RATIO_HEIGHT and "height" if not

  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_DATE_TIME_PAGE_SIZE
};

// currently don't used
enum ARGS_MULTI_CHARTS_PAGE {
  ARG_JS_MC_NAME,
  ARG_TRACES_BLOCKS,
  ARG_DATA_OF_TRACES,
  something1,
  something2,
  something3,
  ARG_MC_DATE_TIME_ASPECT_RATIO_WIDTH,     //%7
  ARG_MC_DATE_TIME_ASPECT_RATIO_HEIGHT,     //%8
  ARG_MC_DATE_ASPECT_WIDTH_OR_HEIGHT, //%9 "width" if ARG_ASPECT_RATIO_WIDTH > ARG_ASPECT_RATIO_HEIGHT and "height" if not

  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_MULTI_CHARTS_PAGE_SIZE
};

enum ARGS_CLOUD_OF_POINTS_PAGE {
  ARG_JS_COF_NAME,
  ARG_X_CLOUD_OF_POINTS,
  ARG_Y_CLOUD_OF_POINTS,
  ARG_COLOR_CLOUD_OF_POINTS,
  ARG_CLOUD_OF_POINTS_ASPECT_RATIO_WIDTH,     //%5
  ARG_CLOUD_OF_POINTS_ASPECT_RATIO_HEIGHT,     //%6
  ARG_CLOUD_OF_POINTS_ASPECT_WIDTH_OR_HEIGHT, //7 "width" if ARG_ASPECT_RATIO_WIDTH > ARG_ASPECT_RATIO_HEIGHT and "height" if not
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_CLOUD_OF_POINTS_PAGE_SIZE
};


extern const char kHtmlModel[];
extern const char kColorMapDefaultPart[];
extern const char kColorMapSunnyPart[];
extern const char kColorMapGlamourPart[];
extern const char kColorMapThermalPart[];
extern const char kColorMapGrayscalePart[];

extern const char kColorMapYlGnBuPart[];
extern const char kColorMapJetPart[];
extern const char kColorMapHotPart[];
extern const char kColorMapElectricPart[];
extern const char kColorMapPortlandPart[];

extern const char kHeatMapTypePart[];
extern const char kSurfaceTypePart[];
extern const char kWarningJSLibAbsentPage[];
extern const char kNoFileFoundedPage[];

extern const char kWarningIcon[];

extern const char kHtmlDateTimeModel[];


extern const char kHtmlMultiChartBlock[];
extern const char kHtmlMultiChartModel[];
extern const char kHtmlCloudOfPoints[];

//#STOP_GRAB_TO_DVS_NAMESPACE
}

#endif // HTML_PARTS_H
