/* Copyright (c) 2024 The DevTools Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the MIT licence.
 * https://github.com/DevToolsOrganization*/


//This file was generated by davis_one_maker.py script.
//Use davis_files.txt and special comments to change generated davis.h and davis.cpp

#ifndef DAVIS_H_
#define DAVIS_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace dvs {
extern const char kAppName[];
extern const char kOutFolderName[];
extern const char kPlotlyJsName[];
extern const char kPlotlyJsResourcePath[];
extern const char kPlotlyJsWorkPath[];
extern const char kWarningPagePath[];

} // namespace dvs end

namespace dv {

enum config_visualizationTypes {
  VISUALTYPE_AUTO, //if user not forces some specific type it will be recognized by context
  VISUALTYPE_CHART,
  VISUALTYPE_HEATMAP,
  VISUALTYPE_SURFACE
};

enum config_colorscales {
  COLORSCALE_DEFAULT,
  COLORSCALE_SUNNY,
  COLORSCALE_GLAMOUR,
  COLORSCALE_THERMAL,
  COLORSCALE_GRAYSCALE,
  COLORSCALE_YlGnBu,
  COLORSCALE_JET,
  COLORSCALE_HOT,
  COLORSCALE_ELECTRIC,
  COLORSCALE_PORTLAND
};


struct commonSettings {
  commonSettings():
    xLabel("X"),
    yLabel("Y") {}
  virtual ~commonSettings() {}
  std::string title;
  std::string xLabel;
  std::string yLabel;
};

struct chartSettings : public commonSettings {
  //currently empty
};

struct heatMapSettings : public commonSettings {
  heatMapSettings():
    colorSc(config_colorscales::COLORSCALE_DEFAULT) {}
  config_colorscales colorSc;
};

struct surfaceSettings : public commonSettings {
  surfaceSettings():
    colorSc(config_colorscales::COLORSCALE_DEFAULT),
    zLabel("Z") {}
  config_colorscales colorSc;
  std::string zLabel;
};


struct Config {
  Config():
    typeVisual(VISUALTYPE_AUTO) {}
  void reset() {
    chart = chartSettings();
    heatmap = heatMapSettings();
    surf = surfaceSettings();
  }

  chartSettings chart;
  heatMapSettings heatmap;
  surfaceSettings surf;

  config_visualizationTypes typeVisual;
};

struct configSaveToDisk {
  configSaveToDisk():
    separatorOfRows("\n"),
    separatorOfCols(";"),
    isTranspose(false) {}
  std::string separatorOfRows;
  std::string separatorOfCols;
  bool isTranspose; //rows-cols or cols-rows
};




} // namespace dv end
namespace dvs {
enum ARGS_INDEX {
  ARG_VALUES,     //%1
  ARG_COLOR_MAP,  //%2
  ARG_MATRIX_TYPE,//%3
  ARG_TITLE,      //%4
  ARG_TITLE_X,    //%5
  ARG_TITLE_Y,    //%6
  ARG_TITLE_Z,    //%7
  ARG_JS_VER,     //%8
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_SIZE
};

enum ARGS_WARNING_PAGE_INDEX {
  ARG_WORKING_FOLDER,
  ARG_JS_VERSION,
  // ADD NEW ENUM BEFORE THIS COMMENT
  ARGS_WARNING_PAGE_SIZE
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

} // namespace dvs end

namespace dvs {
enum SEPARATOR_RESULT {
  GOOD_SEPARATOR,
  MORE_THAN_ONE_SEPARATOR,
  NO_SEPARATOR,
  MABE_COMMA_MABE_DOT,
  UNDEFINED_BEHAVIOR
};
using std::string;
using std::vector;

string getCurrentPath();

bool is_file_exists(const string& file_name);

void openFileBySystem(const string& file_name);

bool isPlotlyScriptExists();

bool saveStringToFile(const string& file_name,
                      const string& data);

void mayBeCreateJsWorkingFolder();

void sleepMs(unsigned long milisec);

void openPlotlyHtml(const string& file_name);

bool get_data_from_file(const string& path,
                        vector<std::string>& result);

vector<string> split(const string& target, char c);

bool readMatrix(vector<vector<double>>& outMatrix, const string& path, char dlmtr);


bool make_string(const string& src,
                 const vector<string>& args,
                 string& out);

// Now it doesn't work.
bool deleteFolder(const char* fname);

int find_separator(const std::string& src,
                   char& separator);

//! remove special characters except letters, numbers and '-', '_'. Spaces -> '_'
string removeSpecialCharacters(const string& s);

//! save to disk vector<T> data
template <typename T>
bool saveVec(const vector<T>& vec, const string& filename, dv::configSaveToDisk config) {
  if (vec.size() == 0) {
    return false;
  }
  std::ofstream fout(filename);
  if (!fout.is_open()) {
    return false;
  }
  size_t rows = vec.size();
  for (int i = 0; i < rows; ++i) {
    fout << vec.at(i) << config.separatorOfRows;
  }
  fout.close();
  return true;
}

//! save to disk vector<vector<T>> data
template <typename T>
bool saveVecVec(const vector<vector<T>>& vecVec, const string& filename, dv::configSaveToDisk config) {
  if (vecVec.size() == 0) {
    return false;
  } else if (vecVec.at(0).size() == 0) {
    return false;
  }

  std::ofstream fout(filename);
  if (!fout.is_open()) {
    return false;
  }
  if (config.isTranspose) {
    size_t rows = vecVec.at(0).size();
    size_t cols = vecVec.size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        double val = vecVec.at(j).at(i);
        fout << val;
        if (j < cols - 1) { // we dont need sep at row end
          fout << config.separatorOfCols;
        }
      }
      fout << config.separatorOfRows;
    }
  } else {
    size_t rows = vecVec.size();
    size_t cols = vecVec.at(0).size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        double val = vecVec.at(i).at(j);
        fout << val;
        if (j < cols - 1) { // we dont need sep at row end
          fout << config.separatorOfCols;
        }
      }
      fout << config.separatorOfRows;
    }
  }
  fout.close();
  return true;
}

//! convert any container to std::vector with G type
template<typename G,
         typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>>>
vector<G> vecFromTemplate(const C& container) {
  vector<G> vec(container.size());
  uint64_t i = 0;
  for (auto v : container) {
    vec[i] = static_cast<G>(v);
    ++i;
  }
  return vec;
}


} // namespace dvs end

namespace dvs {

using std::string;
using std::vector;
using std::istringstream;


bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                string& page,
                                const dv::Config& configuration,
                                dv::config_visualizationTypes typeVisual);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const string& title, const dv::Config& configuration);

bool showHeatMapInBrowser(const string& values, const string& title, const dv::Config& configuration);

bool showLineChartInBrowser(const vector<double>& values, const string& title, const dv::Config& configuration);
bool showLineChartInBrowser(const vector<double>& xValues, const vector<double>& yValues,
                            const string& title, const dv::Config& configuration);

bool showLineChartInBrowser(const string& values, const string& title, const dv::Config& configuration);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const string& title, const dv::Config& configuration);

bool showSurfaceInBrowser(const string& values, const string& title, const dv::Config& configuration);

void showWarningJsAbsentPage();

} // namespace dvs end

namespace dv {

using std::vector;
using std::string;


//! 2-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template <typename T>
bool save(T** data, uint64_t arrRows, uint64_t arrCols, const string& filename,
          const configSaveToDisk& configuration = configSaveToDisk());

//! 1-dimensional array that simulates a 2-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template <typename T>
bool save(const T* data, uint64_t arrRows, uint64_t arrCols, const string& filename,
          const configSaveToDisk& configuration = configSaveToDisk());

//! 1-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template <typename T>
bool save(const T* data, uint64_t count, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());

//! 1-dimensional container
template<typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool show(C const& container, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template<typename C,
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool save(C const& container, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());


//! Two 1-dimensional container for X-Y plots
template<typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool show(C const& containerX, C const& containerY, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template<typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool save(C const& containerX, C const& containerY, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());


//! 2-dimensional container
template<typename C,
         typename E = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename T = std::decay_t<decltype(*begin(std::declval<E>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool show(C const& container_of_containers, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

template<typename C,
         typename E = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename T = std::decay_t<decltype(*begin(std::declval<E>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool save(C const& container_of_containers, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& htmlPageName, const Config& configuration) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (configuration.typeVisual == VISUALTYPE_AUTO ||
      configuration.typeVisual == VISUALTYPE_HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  else if (configuration.typeVisual == VISUALTYPE_SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
  return res;
}

template <typename T>
bool save(T** data, uint64_t arrRows, uint64_t arrCols, const std::string& filename, const configSaveToDisk& configuration) {
  vector<vector<T>> vecVec;
  vecVec.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<T> row(&data[i][0], &data[i][0] + arrCols);
    vecVec.emplace_back(row);
  }
  bool res = dvs::saveVecVec<T>(vecVec, filename, configuration);
  return res;
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& htmlPageName, const Config& configuration) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (configuration.typeVisual == VISUALTYPE_AUTO ||
      configuration.typeVisual == VISUALTYPE_HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  else if (configuration.typeVisual == VISUALTYPE_SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
  return res;
}

template <typename T>
bool save(const T* data, uint64_t arrRows, uint64_t arrCols, const string& filename,
          const configSaveToDisk& configuration) {
  vector<vector<T>> vecVec;
  vecVec.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<T> row(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVec.emplace_back(row);
  }
  bool res = dvs::saveVecVec<T>(vecVec, filename, configuration);
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName, const Config& configuration) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  if (configuration.typeVisual == VISUALTYPE_AUTO ||
      configuration.typeVisual == VISUALTYPE_CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
  return res;
}

template <typename T>
bool save(const T* data, uint64_t count, const string& filename, const configSaveToDisk& configuration) {
  vector<T> row(data, data + count);
  bool res = dvs::saveVec<T>(row, filename, configuration);
  return res;
}

template<typename C, typename T, typename>
bool show(C const& container, const string& htmlPageName, const Config& configuration) {
  vector<double> dblRow = dvs::vecFromTemplate<double>(container);
  bool res = false;
  if (configuration.typeVisual == VISUALTYPE_AUTO ||
      configuration.typeVisual == VISUALTYPE_CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
  return res;
}

template<typename C, typename T, typename>
bool save(C const& container, const string& filename, const configSaveToDisk& configuration) {
  vector<T> row = dvs::vecFromTemplate<T>(container);
  bool res = dvs::saveVec<T>(row, filename, configuration);
  return res;
}

template<typename C, typename T, typename>
bool show(C const& containerX, C const& containerY, const string& htmlPageName, const Config& configuration) {
  if (containerX.size() != containerY.size()) {
    return false;
  }
  vector<double> dblRowX = dvs::vecFromTemplate<double>(containerX);
  vector<double> dblRowY = dvs::vecFromTemplate<double>(containerY);
  bool res = dvs::showLineChartInBrowser(dblRowX, dblRowY, htmlPageName, configuration);
  return res;
}

template<typename C, typename T, typename>
bool save(C const& containerX, C const& containerY,  const string& filename, const configSaveToDisk& configuration) {
  if (containerX.size() != containerY.size()) {
    return false;
  }
  vector<T> rowX = dvs::vecFromTemplate<T>(containerX);
  vector<T> rowY = dvs::vecFromTemplate<T>(containerY);
  vector<vector<T>> vecVec;
  vecVec.emplace_back(rowX);
  vecVec.emplace_back(rowY);
  configSaveToDisk newConf = configuration;
  newConf.isTranspose = !configuration.isTranspose;
  bool res = dvs::saveVecVec<T>(vecVec, filename, newConf);
  return res;
}

template<typename C, typename E, typename T, typename >
bool show(C const& container_of_containers, const string& htmlPageName, const Config& configuration) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(container_of_containers.size());
  for (auto row : container_of_containers) {
    vector<double> dblRow = dvs::vecFromTemplate<double>(row);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  size_t size1 = vecVecDbl.size();
  size_t size2 = 0;
  if (!vecVecDbl.empty()) {
    size2 = vecVecDbl[0].size();
  }
  if ((configuration.typeVisual == VISUALTYPE_AUTO || //case when we want to plot graph with X and Y vectors
       configuration.typeVisual == VISUALTYPE_CHART) &&
      (size1 == 2 || size2 == 2)) { // it can be or 2-columns-data or 2-rows-data
    if (size1 == 2) {
      res = dvs::showLineChartInBrowser(vecVecDbl[0], vecVecDbl[1], htmlPageName, configuration);
    } else if (size2 == 2) {
      vector<double> xVals;
      vector<double> yVals;
      xVals.reserve(size1);
      for (int i = 0; i < size1; ++i) {
        xVals.emplace_back(vecVecDbl[i][0]);
        yVals.emplace_back(vecVecDbl[i][1]);
      }
      res = dvs::showLineChartInBrowser(xVals, yVals, htmlPageName, configuration);
    }
  } else if (configuration.typeVisual == VISUALTYPE_AUTO ||
             configuration.typeVisual == VISUALTYPE_HEATMAP) {
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  } else if (configuration.typeVisual == VISUALTYPE_SURFACE) {
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
  }
  return res;
}

template<typename C, typename E, typename T, typename >
bool save(C const& container_of_containers, const string& filename, const configSaveToDisk& configuration) {
  vector<vector<T>> vecVec;
  vecVec.reserve(container_of_containers.size());
  for (auto row : container_of_containers) {
    vector<T> rowTemp = dvs::vecFromTemplate<T>(row);
    vecVec.emplace_back(rowTemp);
  }
  bool res = dvs::saveVecVec<T>(vecVec, filename, configuration);
  return res;
}


} // namespace dv end

#endif // DAVIS_H_