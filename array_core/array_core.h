#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_

#include <iostream>
#include <vector>
#include "plotly_maker/plotly_maker.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"

namespace davis {

using std::vector;
using std::string;


//! two-dimensional vector
template <typename T>
bool show(const vector<vector<T>>& data, const string& title = kAppName,
          ShowSettings* settings = nullptr);

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName,  ShowSettings* settings = nullptr);

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName,  ShowSettings* settings = nullptr);

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& title = kAppName,
          ShowSettings* settings = nullptr);

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& title = kAppName,
          ShowSettings* settings = nullptr);

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& title,
          ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if(settings == nullptr){
    settings = new ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& title,
          ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if(settings == nullptr){
    settings = new ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& title,
          ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if(settings == nullptr){
    settings = new ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(const vector<T>& data, const string& title,
          ShowSettings *settings) {
  vector<double> dblRow(data.begin(), data.end());
  bool res = false;
  std::unique_ptr<ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if(settings == nullptr){
    settings = new ShowSettingsChart();
    smartP.reset(settings);
  }
  if (settings->visualType == davis::visualizationTypes::CHART)
    res = davis::showLineChartInBrowser(dblRow, title, static_cast<const ShowSettingsChart*>(settings));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& title,
          ShowSettings *settings) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  std::unique_ptr<ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if(settings == nullptr){
    settings = new ShowSettingsChart();
    smartP.reset(settings);
  }
  if (settings->visualType == davis::visualizationTypes::CHART)
    res = davis::showLineChartInBrowser(dblRow, title, static_cast<const ShowSettingsChart*>(settings));
  return res;
}

} // namespace davis

#endif //ARRAY_CORE_ARRAY_CORE_H_
