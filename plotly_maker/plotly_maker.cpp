#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "html_parts.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"
#include "plotly_maker.h"
#include <sstream>
#include <iostream>

namespace {

using std::vector;
using std::string;



bool checkThatSizesAreTheSame(const std::vector<std::vector<double>> &values) {
  size_t size = 0;
  if(!values.empty()) {
    size = values[0].size();
  };
  for(unsigned int i=0;i<values.size();++i){

    if(values[i].size() != size)return false;
  }
  return true;
}

bool createStringHeatMapValues(const vector<vector<double>> &values,
                               string &str_values){
  if(!checkThatSizesAreTheSame(values))return false;
  if(!str_values.empty())str_values.clear();
  str_values.append(R"(var data = [{z: )");
  str_values.append(R"([)");
  for (unsigned int i = 0; i < values.size(); ++i) {
    str_values.append("[");
    for (unsigned int j = 0; j < values[i].size(); ++j) {
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


bool createStringLineChartValues(const std::vector<double>& values,
                                 std::string& str_values) {
  if (!str_values.empty()) {
    str_values.clear();
  }
  str_values = R"(var trace = {
x: [)";
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
  str_values.append("], mode: 'lines+markers'};var data = [trace];");
  return true;
}

inline bool heatmap_and_surface(const vector<vector<double>>& values,
                                const std::string& title,
                                const davis::showSettings& settings) {
  std::string page;
  if (!createHtmlPageWithPlotlyJS(values, page, settings)) {
    return false;
  }
  std::string pageName;
  davis::mayBeCreateJsWorkingFolder();
  pageName.append("./").append(davis::kOutFolderName).append(title).append(".html");
  davis::saveStringToFile(pageName, page);
  davis::openPlotlyHtml(pageName);
  return true;// TODO handle different exceptions
};

} // namespace

namespace davis {
using std::string;
using std::vector;
using std::istringstream;


bool createHtmlPageWithPlotlyJS(const std::vector<std::vector<double>>& values,
                                std::string& page,
                                const davis::showSettings& settings) {
  page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  if (!checkThatSizesAreTheSame(values)) {
    return false;
  }
  createStringHeatMapValues(values, str_values);
  page.append(str_values);
  switch (settings.colorscale) {
    case colorscales::DEFAULT:
      page.append(kColorMapDefaultPart);
      break;
    case colorscales::SUNNY:
      page.append(kColorMapSunnyPart);
      break;
    case colorscales::GLAMOUR:
      page.append(kColorMapGlamourPart);
      break;
    case colorscales::THERMAL:
      page.append(kColorMapThermalPart);
      break;
  }
  switch (settings.visualType) {
    case visualizationTypes::CHART:
      break;
    case visualizationTypes::HEATMAP:
      page.append(kHeatMapTypePart);
      break;
    case visualizationTypes::SURFACE:
      page.append(kSurfaceTypePart);
      break;
  }
  page.append(kCommonLastPart);
  return true;
}

bool showHeatMapInBrowser(const vector<vector<double>>& values,
                          const std::string& title,
                          const showSettings& settings) {
  return heatmap_and_surface(values, title, settings);
}

bool showHeatMapInBrowser(const std::string& values,
                          const std::string& title,
                          const showSettings& settings) {
  vector<vector<double>>heat_map_values;
  getMatrixValuesFromString(values, heat_map_values);
  showHeatMapInBrowser(heat_map_values, title, settings);
  return true;
};

bool showLineChartInBrowser(const vector<double>& values,
                            const std::string& title,
                            const showSettings& settings) {
  std::string page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  createStringLineChartValues(values, str_values);
  page.append(str_values);
  page.append(kCommonLastPart);
  std::string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  davis::saveStringToFile(pageName, page);
  openPlotlyHtml(pageName);
  return true;
}

bool showLineChartInBrowser(const std::string& values,
                            const std::string& title,
                            const showSettings& settings) {
  std::vector<double>vals;
  std::istringstream f(values);
  std::string s;
  while (std::getline(f, s, ',')) {
    vals.push_back(std::stod(s));
  }
  showLineChartInBrowser(vals, title, settings);
  return true;
};

bool showSurfaceInBrowser(const vector<vector<double>>& values,
                          const std::string& title,
                          const showSettings& settings) {
  return heatmap_and_surface(values, title, settings);
}

bool showSurfaceInBrowser(const std::string& values,
                          const std::string& title,
                          const showSettings& settings) {
  vector<vector<double>>surface_values;
  getMatrixValuesFromString(values, surface_values);
  showSurfaceInBrowser(surface_values, title, settings);
  return true;
}

bool getMatrixValuesFromString(const std::string& in_values,
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
}

}; // namespace davis

