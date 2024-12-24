//#START_GRAB_TO_INCLUDES_LIST
#include <iostream>
#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
//#STOP_GRAB_TO_INCLUDES_LIST

#include "html_parts.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"
#include "plotly_maker.h"
#include "array_core/multi_plot.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE



bool checkThatSizesAreTheSame(const vector<vector<double>>& values) {
  size_t size = 0;
  if (!values.empty()) {
    size = values[0].size();
  };
  for (size_t i = 0; i < values.size(); ++i) {

    if (values[i].size() != size) {
      showMatrixSizesAreNotTheSame(i);
      return false;
    }
  }
  return true;
}

bool createStringHeatMapValues(const vector<vector<double>>& values,
                               string& str_values) {
  if (!checkThatSizesAreTheSame(values))
    return false;
  if (!str_values.empty())
    str_values.clear();
  str_values.append(R"(var data = [{z: )");
  str_values.append(R"([)");
  for (size_t i = 0; i < values.size(); ++i) {
    str_values.append("[");
    for (size_t j = 0; j < values[i].size(); ++j) {
      str_values.append(nullIfNotFinite(values[i][j]));
      if (j != values[i].size() - 1) {
        str_values.append(",");
      }
    }
    str_values.append("]");
    if (i != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append(R"(],)");
  return true;
}

bool createStringLineChartValues(const vector<double>& xValues,
                                 const vector<double>& yValues,
                                 string& out_str_values) {
  if (xValues.size() != yValues.size()) {
    return false;
  }

  if (!out_str_values.empty()) {
    out_str_values.clear();
  }
  out_str_values = R"(var trace = {x: [)";
  for (size_t i = 0; i < xValues.size(); ++i) {
    out_str_values.append(nullIfNotFinite(xValues[i]));
    if (i != xValues.size() - 1) {
      out_str_values.append(",");
    }
  }
  out_str_values.append("], y: [");
  for (size_t j = 0; j < yValues.size(); ++j) {
    out_str_values.append(nullIfNotFinite(yValues[j]));
    if (j != yValues.size() - 1) {
      out_str_values.append(",");
    }
  }
  out_str_values.append("], mode: 'lines', hovertemplate: 'x:%{x}, y:%{y:.} <extra></extra>' };var data = [trace];");
  return true;
}



inline bool heatmap_and_surface(const vector<vector<double>>& values,
                                const string& title,
                                const dv::Config& configuration,
                                dv::config_visualizationTypes typeVisual) {
  string page;
  if (!createHtmlPageWithPlotlyJS(values, page, configuration, typeVisual)) {
    return false;
  }
  string pageName;
  mayBeCreateJsWorkingFolder();
  string titleWithoutSpecialChars = dvs::removeSpecialCharacters(title);
  pageName.append("./").append(kOutFolderName).append(titleWithoutSpecialChars).append(".html");
  saveStringToFile(pageName, page);
  if (isPlotlyScriptExists()) {
    openPlotlyHtml(pageName);
  } else {
    showWarningJsAbsentPage();
  }
  return true;// TODO handle different exceptions
};

bool getMatrixValuesFromString(const string& in_values,
                               vector<vector<double>>& out_values) {
  istringstream f_lines(in_values);
  string lines;
  while (std::getline(f_lines, lines, ';')) {
    vector<double>vals;
    istringstream f_values(lines);
    string str_value;
    while (std::getline(f_values, str_value, ',')) {
      vals.push_back(std::stod(str_value));
    }
    out_values.push_back(vals);
  }
  return true;
};

bool createHtmlPageWithPlotlyJS(const std::vector<std::vector<double>>& values,
                                string& page,
                                const dv::Config& configuration,
                                dv::config_visualizationTypes typeVisual) {
  vector<string> args(ARGS_SIZE, "");
  string str_values = "";
  if (!checkThatSizesAreTheSame(values)) {
    return false;
  }
  createStringHeatMapValues(values, str_values);
  args[ARG_VALUES] = str_values;
  args[ARG_JS_VER] = kPlotlyJsName;
  dv::config_colorscales clrScale;
  if (typeVisual == dv::VISUALTYPE_HEATMAP)
    clrScale = configuration.heatmap.colorSc;
  else if (typeVisual == dv::VISUALTYPE_SURFACE)
    clrScale = configuration.surf.colorSc;
  else
    return false;
  switch (clrScale) {
    case dv::config_colorscales::COLORSCALE_DEFAULT:
      args[ARG_COLOR_MAP] = kColorMapDefaultPart;
      break;
    case dv::config_colorscales::COLORSCALE_SUNNY:
      args[ARG_COLOR_MAP] = kColorMapSunnyPart;
      break;
    case dv::config_colorscales::COLORSCALE_GLAMOUR:
      args[ARG_COLOR_MAP] = kColorMapGlamourPart;
      break;
    case dv::config_colorscales::COLORSCALE_THERMAL:
      args[ARG_COLOR_MAP] = kColorMapThermalPart;
      break;
    case dv::config_colorscales::COLORSCALE_GRAYSCALE:
      args[ARG_COLOR_MAP] = kColorMapGrayscalePart;
      break;
    case dv::config_colorscales::COLORSCALE_YlGnBu:
      args[ARG_COLOR_MAP] = kColorMapYlGnBuPart;
      break;
    case dv::config_colorscales::COLORSCALE_JET:
      args[ARG_COLOR_MAP] = kColorMapJetPart;
      break;
    case dv::config_colorscales::COLORSCALE_HOT:
      args[ARG_COLOR_MAP] = kColorMapHotPart;
      break;
    case dv::config_colorscales::COLORSCALE_ELECTRIC:
      args[ARG_COLOR_MAP] = kColorMapElectricPart;
      break;
    case dv::config_colorscales::COLORSCALE_PORTLAND:
      args[ARG_COLOR_MAP] = kColorMapPortlandPart;
      break;
  }
  switch (typeVisual) {
    case dv::VISUALTYPE_HEATMAP: {
      args[ARG_MATRIX_TYPE] = kHeatMapTypePart;
      args[ARG_TITLE] = configuration.heatmap.title;
      args[ARG_TITLE_X] = configuration.heatmap.xLabel;
      args[ARG_TITLE_Y] = configuration.heatmap.yLabel;
      args[ARG_ASPECT_RATIO_WIDTH] = dvs::toStringDotSeparator(configuration.heatmap.aspectRatioWidth);
      args[ARG_ASPECT_RATIO_HEIGHT] = dvs::toStringDotSeparator(configuration.heatmap.aspectRatioHeight);
      string paramWH;
      if (configuration.heatmap.aspectRatioWidth > configuration.heatmap.aspectRatioHeight) {
        paramWH = "width";
      } else {
        paramWH = "height";
      }
      args[ARG_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
      break;
    }
    case dv::VISUALTYPE_SURFACE: {
      args[ARG_MATRIX_TYPE] = kSurfaceTypePart;
      args[ARG_TITLE] = configuration.surf.title;
      args[ARG_TITLE_X] = configuration.surf.xLabel;
      args[ARG_TITLE_Y] = configuration.surf.yLabel;
      args[ARG_TITLE_Z] = configuration.surf.zLabel;
      args[ARG_ASPECT_RATIO_WIDTH] = dvs::toStringDotSeparator(configuration.surf.aspectRatioWidth);
      args[ARG_ASPECT_RATIO_HEIGHT] = dvs::toStringDotSeparator(configuration.surf.aspectRatioHeight);
      string paramWH;
      if (configuration.surf.aspectRatioWidth > configuration.surf.aspectRatioHeight) {
        paramWH = "width";
      } else {
        paramWH = "height";
      }
      args[ARG_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
      break;
    }
    default:
      break;
  }

  make_string(kHtmlModel, args, page);
  return true;
}

bool showHeatMapInBrowser(const vector<vector<double>>& values,
                          const string& title, const dv::Config& configuration) {
  return heatmap_and_surface(values, title, configuration, dv::VISUALTYPE_HEATMAP);
}

bool showHeatMapInBrowser(const string& values,
                          const string& title, const dv::Config& configuration) {
  vector<vector<double>>heat_map_values;
  getMatrixValuesFromString(values, heat_map_values);
  showHeatMapInBrowser(heat_map_values, title, configuration);
  return true;
};

bool showLineChartInBrowser(const vector<double>& values,
                            const string& title, const dv::Config& configuration) {

  vector<double> x(values.size());
  std::iota(std::begin(x), std::end(x), 0);  // Fill with 0, 1, 2...
  showLineChartInBrowser(x, values, title, configuration);
  return true;
}

bool showLineChartInBrowser(const vector<double>& xValues, const vector<double>& yValues,
                            const std::string& title, const dv::Config& configuration) {
  string page;
  vector<string>args(ARGS_SIZE, "");
  args[ARG_JS_VER] = kPlotlyJsName;
  string str_values = "";
  createStringLineChartValues(xValues, yValues, str_values);
  args[ARG_VALUES] = str_values;
  args[ARG_TITLE] = configuration.chart.title;
  args[ARG_TITLE_X] = configuration.chart.xLabel;
  args[ARG_TITLE_Y] = configuration.chart.yLabel;
  args[ARG_ASPECT_RATIO_WIDTH] = dvs::toStringDotSeparator(configuration.chart.aspectRatioWidth);
  args[ARG_ASPECT_RATIO_HEIGHT] = dvs::toStringDotSeparator(configuration.chart.aspectRatioHeight);
  string paramWH;
  if (configuration.chart.aspectRatioWidth > configuration.chart.aspectRatioHeight) {
    paramWH = "width";
  } else {
    paramWH = "height";
  }
  args[ARG_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
  make_string(kHtmlModel, args, page);
  string pageName;
  mayBeCreateJsWorkingFolder();
  string titleWithoutSpecialChars = dvs::removeSpecialCharacters(title);
  pageName.append("./").append(kOutFolderName).append(titleWithoutSpecialChars).append(".html");
  saveStringToFile(pageName, page);
  if (isPlotlyScriptExists()) {
    openPlotlyHtml(pageName);
  } else {
    showWarningJsAbsentPage();
  }
  return true;
}

bool showLineChartInBrowser(const string& values,
                            const string& title, const dv::Config& configuration) {
  vector<double>vals;
  istringstream f(values);
  string s;
  while (std::getline(f, s, ',')) {
    vals.push_back(std::stod(s));
  }
  showLineChartInBrowser(vals, title, configuration);
  return true;
};

bool showSurfaceInBrowser(const vector<vector<double>>& values,
                          const string& title, const dv::Config& configuration) {
  return heatmap_and_surface(values, title, configuration, dv::VISUALTYPE_SURFACE);
}

bool showSurfaceInBrowser(const string& values,
                          const string& title, const dv::Config& configuration) {
  vector<vector<double>>surface_values;
  getMatrixValuesFromString(values, surface_values);
  showSurfaceInBrowser(surface_values, title, configuration);
  return true;
}

void showWarningJsAbsentPage() {
  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_WARNING_PAGE_SIZE, ""};
  args[ARG_WORKING_FOLDER] = getCurrentPath() + davis_dir;
  args[ARG_JS_VERSION] = kPlotlyJsName;
  make_string(kWarningJSLibAbsentPage, args, out);
  saveStringToFile(kWarningPagePath, out);
  openFileBySystem(kWarningPagePath);
}


void showReportPage(const string& title,
                    const string& svg,
                    const string& description) {

  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_REPORT_PAGE_SIZE, ""};
  args[ARG_REPORT_TITLE] = title;
  args[ARG_SVG_ICON] = svg;
  args[ARG_REPORT_DESCRIPTION] = description;
  make_string(kNoFileFoundedPage, args, out);
  saveStringToFile(kReportPagePath, out);
  openFileBySystem(kReportPagePath);

}


void showReportFileNotFounded() {

  showReportPage("Open file error.",
                 kWarningIcon,
                 "File is not founded. Please, check the path to the file.");
}

void showReportFileEmpty() {

  showReportPage("File is empty.",
                 kWarningIcon,
                 "No data to show.");
}


void showMatrixSizesAreNotTheSame(int badRow) {

  string text;
  text.append("Rows have different sizes in matrix. Check the row № ").append(std::to_string(badRow + 1));
  showReportPage("Rows sizes are not the same",
                 kWarningIcon,
                 text);
}

void showDateTimeChart(const string& date_time_values,
                       const vector<double>& yValues) {

  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_DATE_TIME_PAGE_SIZE, ""};
  args[ARG_JS_NAME] = kPlotlyJsName;

  vector<string>args_block {ARGS_SIMPLE_DATA_BLOCK_SIZE, ""};
  std::string simpleData_yValues = vectorToString(yValues);
  args_block[ARG_SIMPLE_DATA_X] = date_time_values;
  args_block[ARG_SIMPLE_DATA_Y] = simpleData_yValues;
  std::string data_values_block;
  make_string(kHtmlSimpleDataBlock, args_block, data_values_block);


  args[ARG_DATE_TIME_VALUES_BLOCK] = data_values_block;
  args[ARG_DATE_TIME_ASPECT_RATIO_WIDTH] = "1";
  args[ARG_DATE_TIME_ASPECT_RATIO_HEIGHT] = "1";
  /*
  string paramWH;
  if(configuration.chart.aspectRatioWidth > configuration.chart.aspectRatioHeight){
    paramWH = "width";
  }else{
    paramWH = "height";
  }
  */
  string paramWH = "height";
  args[ARG_DATE_TIME_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
  make_string(kHtmlDateTimeModel, args, out);
  saveStringToFile(kReportPagePath, out);
  openFileBySystem(kReportPagePath);


}

void addTraceBlockToGlobal(const vector<double>& yValues, const string& traceName) {
  vector<double> xValues(yValues.size());
  std::iota(std::begin(xValues), std::end(xValues), 0);  // Fill with 0, 1, 2...
  addTraceBlockToGlobal(xValues, yValues, traceName);
}

void addTraceBlockToGlobal(const vector<double>& xValues, const vector<double>& yValues, const string& traceName) {
  string trace_block = dvs::kHtmlMultiChartBlock;
  int trace_i = 1 + dvs::allChartBlocks.size();
  string str_numTrace = std::to_string(trace_i);
  string str_values_x = vectorToString(xValues);
  string str_values_y = vectorToString(yValues);

  vector<string> args = {str_numTrace, str_values_x, str_values_y, traceName};
  string filled_trace_block = "";
  make_string(trace_block, args, filled_trace_block);
  dvs::allChartBlocks.emplace_back(filled_trace_block);
}

void showCloudOfPointsChart(const vector<double>& xValues,
                            const vector<double>& yValues,
                            const vector<double>& colorValues) {
  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_CLOUD_OF_POINTS_PAGE_SIZE, ""};
  args[ARG_JS_COF_NAME] = kPlotlyJsName;
  args[ARG_X_CLOUD_OF_POINTS] = vectorToString(xValues);
  args[ARG_Y_CLOUD_OF_POINTS] = vectorToString(yValues);
  args[ARG_COLOR_CLOUD_OF_POINTS] = vectorToString(colorValues);
  args[ARG_CLOUD_OF_POINTS_ASPECT_RATIO_WIDTH] = "1";
  args[ARG_CLOUD_OF_POINTS_ASPECT_RATIO_HEIGHT] = "1";
  /*
  string paramWH;
  if(configuration.chart.aspectRatioWidth > configuration.chart.aspectRatioHeight){
    paramWH = "width";
  }else{
    paramWH = "height";
  }
  */
  string paramWH = "height";
  args[ARG_CLOUD_OF_POINTS_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
  make_string(kHtmlCloudOfPoints, args, out);
  saveStringToFile(kCloudPagePath, out);
  openFileBySystem(kCloudPagePath);
}

void showCloudOfPointsChartStr(const std::string& xValues,
                               const vector<double>& yValues,
                               const vector<double>& colorValues) {
  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_CLOUD_OF_POINTS_PAGE_SIZE, ""};
  args[ARG_JS_COF_NAME] = kPlotlyJsName;
  args[ARG_X_CLOUD_OF_POINTS] = xValues;
  args[ARG_Y_CLOUD_OF_POINTS] = vectorToString(yValues);
  args[ARG_COLOR_CLOUD_OF_POINTS] = vectorToString(colorValues);
  args[ARG_CLOUD_OF_POINTS_ASPECT_RATIO_WIDTH] = "1";
  args[ARG_CLOUD_OF_POINTS_ASPECT_RATIO_HEIGHT] = "1";
  /*
  string paramWH;
  if(configuration.chart.aspectRatioWidth > configuration.chart.aspectRatioHeight){
    paramWH = "width";
  }else{
    paramWH = "height";
  }
  */
  string paramWH = "height";
  args[ARG_CLOUD_OF_POINTS_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
  make_string(kHtmlCloudOfPoints, args, out);
  saveStringToFile(kCloudPagePath, out);
  openFileBySystem(kCloudPagePath);
}

void showDateTimeMultichart(const std::string& date_time_values,
                            const vector<vector<double>>& yValues) {
  string out;
  string davis_dir;
#ifdef _WIN32
  davis_dir = "\\davis_htmls";
#elif __linux__
  davis_dir = "/davis_htmls";
#endif
  vector<string>args {ARGS_DATE_TIME_PAGE_SIZE, ""};
  args[ARG_JS_NAME] = kPlotlyJsName;


  std::string all_data = "";
  for (int i = 0; i < yValues.size(); ++i) {
    vector<string>args_block {ARGS_SIMPLE_DATA_BLOCK_SIZE, ""};
    std::string simpleData_yValues = vectorToString(yValues[i]);
    args_block[ARG_SIMPLE_DATA_X] = date_time_values;
    args_block[ARG_SIMPLE_DATA_Y] = simpleData_yValues;
    std::string data_values_block;
    make_string(kHtmlSimpleDataBlock, args_block, data_values_block);
    all_data.append(data_values_block);
    if (i != yValues.size() - 1) {
      all_data.append(",");
    }
  }

  args[ARG_DATE_TIME_VALUES_BLOCK] = all_data;
  args[ARG_DATE_TIME_ASPECT_RATIO_WIDTH] = "1";
  args[ARG_DATE_TIME_ASPECT_RATIO_HEIGHT] = "1";

  string paramWH = "height";
  args[ARG_DATE_TIME_ASPECT_WIDTH_OR_HEIGHT] = paramWH;
  make_string(kHtmlDateTimeModel, args, out);
  saveStringToFile(kReportPagePath, out);
  openFileBySystem(kReportPagePath);
}

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

