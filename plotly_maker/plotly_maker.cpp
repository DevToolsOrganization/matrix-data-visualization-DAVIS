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
                                const dv::Config& configuration,
                                dv::config_visualizationTypes typeVisual) {
  string page;
  if (!createHtmlPageWithPlotlyJS(values, page, configuration, typeVisual)) {
    return false;
  }
  string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  saveStringToFile(pageName, page);
  if(isPlotlyScriptExists()){
  openPlotlyHtml(pageName);
  }else{
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
  }
  switch (typeVisual) {
    case dv::VISUALTYPE_HEATMAP:
      args[ARG_MATRIX_TYPE] = kHeatMapTypePart;
      args[ARG_TITLE] = configuration.heatmap.title;
      args[ARG_TITLE_X] = configuration.heatmap.xLabel;
      args[ARG_TITLE_Y] = configuration.heatmap.yLabel;
      break;
    case dv::VISUALTYPE_SURFACE:
      args[ARG_MATRIX_TYPE] = kSurfaceTypePart;
      args[ARG_TITLE] = configuration.surf.title;
      args[ARG_TITLE_X] = configuration.surf.xLabel;
      args[ARG_TITLE_Y] = configuration.surf.yLabel;
      args[ARG_TITLE_Z] = configuration.surf.zLabel;
      break;
    case dv::VISUALTYPE_CHART:
      args[ARG_TITLE] = configuration.chart.title;
      args[ARG_TITLE_X] = configuration.chart.xLabel;
      args[ARG_TITLE_Y] = configuration.chart.yLabel;
      break;
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
  string page;
  vector<string>args(ARGS_SIZE, "");
  string str_values = "";
  createStringLineChartValues(values, str_values);
  args[ARG_VALUES] = str_values;
  args[ARG_TITLE] = configuration.chart.title;
  args[ARG_TITLE_X] = configuration.chart.xLabel;
  args[ARG_TITLE_Y] = configuration.chart.yLabel;
  make_string(kHtmlModel, args, page);
  string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  saveStringToFile(pageName, page);
  if(isPlotlyScriptExists()){
  openPlotlyHtml(pageName);
  }else{
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
    vector<string>args = {getCurrentPath()+davis_dir};
    make_string(kWarningJSLibAbsentPage,args,out);
    saveStringToFile(kWarningPagePath, out);
  openFileBySystem(kWarningPagePath);
}
//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

