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

using std::string;
using std::vector;
using std::istringstream;

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
                                const std::string& title,
                                const dv::conf_visualizationTypes& type) {
  std::string page;
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
                                std::string& page,
                                const dv::conf_visualizationTypes& type) {
  page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  if (!checkThatSizesAreTheSame(values)) {
    return false;
  }
  createStringHeatMapValues(values, str_values);
  page.append(str_values);
  dv::conf_colorscales clrScale;
  if (type == dv::conf_visualizationTypes::HEATMAP)
    clrScale = dv::config().heatmap.colorSc;
  else if (type == dv::conf_visualizationTypes::SURFACE)
    clrScale = dv::config().surf.colorSc;
  switch (clrScale) {
    case dv::conf_colorscales::DEFAULT:
      page.append(kColorMapDefaultPart);
      break;
    case dv::conf_colorscales::SUNNY:
      page.append(kColorMapSunnyPart);
      break;
    case dv::conf_colorscales::GLAMOUR:
      page.append(kColorMapGlamourPart);
      break;
    case dv::conf_colorscales::THERMAL:
      page.append(kColorMapThermalPart);
      break;
    case dv::conf_colorscales::GRAYSCALE:
      page.append(kColorMapGrayscalePart);
      break;
  }
  //Вопрос с автотипом.
  // Если пользователь задает тип AUTO, то по ходу дела алгоритм сам должен понимать, что сейчас отображать
  // Но этот автоРазбор должен был сделан раньше, чем в этой функции.
  // Предлагаю: добавить приватный член класса Configurator, в котором будет полe notForUser_visualType.
  // Это поле заполняется само.
  switch (type) {
    case dv::conf_visualizationTypes::HEATMAP:
      page.append(kHeatMapTypePart);
      break;
    case dv::conf_visualizationTypes::SURFACE:
      page.append(kSurfaceTypePart);
      break;
    default:
      break;
  }
  page.append(kCommonLastPart);
  return true;
}

bool showHeatMapInBrowser(const vector<vector<double>>& values,
                          const std::string& title) {
  return heatmap_and_surface(values, title, dv::conf_visualizationTypes::HEATMAP);
}

bool showHeatMapInBrowser(const std::string& values,
                          const std::string& title) {
  vector<vector<double>>heat_map_values;
  getMatrixValuesFromString(values, heat_map_values);
  showHeatMapInBrowser(heat_map_values, title);
  return true;
};

bool showLineChartInBrowser(const vector<double>& values,
                            const string& title) {
  string page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  createStringLineChartValues(values, str_values);
  page.append(str_values);
  page.append(kCommonLastPart);
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
  return heatmap_and_surface(values, title, dv::conf_visualizationTypes::SURFACE);
}

bool showSurfaceInBrowser(const std::string& values,
                          const string& title) {
  vector<vector<double>>surface_values;
  getMatrixValuesFromString(values, surface_values);
  showSurfaceInBrowser(surface_values, title);
  return true;
}

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

