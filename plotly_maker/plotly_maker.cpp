//#START_GRAB_TO_INCLUDES_LIST
#include <iostream>
#include <vector>
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


namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE



bool checkThatSizesAreTheSame(const vector<vector<double>>& values) {
  size_t size = 0;
  if (!values.empty()) {
    size = values[0].size();
  };
  for (size_t i = 0; i < values.size(); ++i) {

    if (values[i].size() != size)
      return false;
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
      str_values.append(std::to_string(values[i][j]));
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


bool createStringLineChartValues(const vector<double>& values,
                                 string& str_values) {
  if (!str_values.empty()) {
    str_values.clear();
  }
  str_values = R"(var trace = {x: [)";
  for (size_t i = 0; i < values.size(); ++i) {
    str_values.append(std::to_string(i));
    if (i != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append("], y: [");
  for (size_t j = 0; j < values.size(); ++j) {
    str_values.append(std::to_string(values[j]));
    if (j != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append("], mode: 'lines+markers', hovertemplate: 'x:%{x}, y:%{y:.} <extra></extra>' };var data = [trace];");
  return true;
}

inline bool heatmap_and_surface(const vector<vector<double>>& values,
                                const string& title,
                                const dv::config_visualizationTypes& type) {
  dv::config().common.title = title;
  string page;
  if (!createHtmlPageWithPlotlyJS(values, page, type)) {
    return false;
  }
  string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  saveStringToFile(pageName, page);
  openPlotlyHtml(pageName);
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
                                const dv::config_visualizationTypes& type) {
  vector<string> args(ARGS_SIZE, "");
  string str_values = "";
  if (!checkThatSizesAreTheSame(values)) {
    return false;
  }
  createStringHeatMapValues(values, str_values);
  args[ARG_VALUES] = str_values;
  dv::config_colorscales clrScale;
  if (type == dv::config_visualizationTypes::VISUALTYPE_HEATMAP)
    clrScale = dv::config().heatmap.colorSc;
  else if (type == dv::config_visualizationTypes::VISUALTYPE_SURFACE)
    clrScale = dv::config().surf.colorSc;
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
  }
  switch (type) {
    case dv::config_visualizationTypes::VISUALTYPE_HEATMAP:
      args[ARG_MATRIX_TYPE] = kHeatMapTypePart;
      break;
    case dv::config_visualizationTypes::VISUALTYPE_SURFACE:
      args[ARG_MATRIX_TYPE] = kSurfaceTypePart;
      break;
    default:
      break;
  }
  args[ARG_TITLE] = dv::config().common.title;
  args[ARG_TITLE_X] = dv::config().common.xLabel;
  args[ARG_TITLE_Y] = dv::config().common.yLabel;
  make_string(kHtmlModel, args, page);
  return true;
}

bool showHeatMapInBrowser(const vector<vector<double>>& values,
                          const string& title) {
  return heatmap_and_surface(values, title, dv::config_visualizationTypes::VISUALTYPE_HEATMAP);
}

bool showHeatMapInBrowser(const string& values,
                          const string& title) {
  vector<vector<double>>heat_map_values;
  getMatrixValuesFromString(values, heat_map_values);
  showHeatMapInBrowser(heat_map_values, title);
  return true;
};

bool showLineChartInBrowser(const vector<double>& values,
                            const string& title) {
  dv::config().common.title = title;
  string page;
  vector<string>args(ARGS_SIZE, "");
  string str_values = "";
  createStringLineChartValues(values, str_values);
  args[ARG_VALUES] = str_values;
  args[ARG_TITLE] = dv::config().common.title;
  args[ARG_TITLE_X] = dv::config().common.xLabel;
  args[ARG_TITLE_Y] = dv::config().common.yLabel;
  make_string(kHtmlModel, args, page);
  string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  saveStringToFile(pageName, page);
  openPlotlyHtml(pageName);
  return true;
}

bool showLineChartInBrowser(const string& values,
                            const string& title) {
  vector<double>vals;
  istringstream f(values);
  string s;
  while (std::getline(f, s, ',')) {
    vals.push_back(std::stod(s));
  }
  showLineChartInBrowser(vals, title);
  return true;
};

bool showSurfaceInBrowser(const vector<vector<double>>& values,
                          const string& title) {
  return heatmap_and_surface(values, title, dv::config_visualizationTypes::VISUALTYPE_SURFACE);
}

bool showSurfaceInBrowser(const string& values,
                          const string& title) {
  vector<vector<double>>surface_values;
  getMatrixValuesFromString(values, surface_values);
  showSurfaceInBrowser(surface_values, title);
  return true;
}

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

