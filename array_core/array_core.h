#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_
//#START_GRAB_TO_INCLUDES_LIST
#include <iostream>
#include <vector>
//#STOP_GRAB_TO_INCLUDES_LIST
#include "plotly_maker/plotly_maker.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"
#include "configurator.h"

namespace dv {
//#START_GRAB_TO_DV_NAMESPACE



using std::vector;
using std::string;


//! two-dimensional vector
template <typename T>
bool show(const vector<vector<T>>& data, const string& title = dvs::kAppName,
          dvs::ShowSettings* settings = nullptr);

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& title = dvs::kAppName,  dvs::ShowSettings* settings = nullptr);

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& title = dvs::kAppName,  dvs::ShowSettings* settings = nullptr);

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& title = dvs::kAppName,
          dvs::ShowSettings* settings = nullptr);

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& title = dvs::kAppName,
          dvs::ShowSettings* settings = nullptr);

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& title,
          dvs::ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<dvs::ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if (settings == nullptr) {
    settings = new dvs::ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->getVisualType() == dvs::visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsHeatMap*>(settings));
  else if (settings->getVisualType() == dvs::visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& title,
          dvs::ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<dvs::ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if (settings == nullptr) {
    settings = new dvs::ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->getVisualType() == dvs::visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsHeatMap*>(settings));
  else if (settings->getVisualType() == dvs::visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& title,
          dvs::ShowSettings *settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  std::unique_ptr<dvs::ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if (settings == nullptr) {
    settings = new dvs::ShowSettingsHeatMap();
    smartP.reset(settings);
  }
  if (settings->getVisualType() == dvs::visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsHeatMap*>(settings));
  else if (settings->getVisualType() == dvs::visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, title, static_cast<const dvs::ShowSettingsSurface*>(settings));
  return res;
}

template <typename T>
bool show(const vector<T>& data, const string& title,
          dvs::ShowSettings* settings) {
  vector<double> dblRow(data.begin(), data.end());
  bool res = false;
  std::unique_ptr<dvs::ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if (settings == nullptr) {
    settings = new dvs::ShowSettingsChart();
    smartP.reset(settings);
  }
  if (settings->getVisualType() == dvs::visualizationTypes::CHART)
    res = dvs::showLineChartInBrowser(dblRow, title, static_cast<const dvs::ShowSettingsChart*>(settings));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& title,
          dvs::ShowSettings *settings) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  std::unique_ptr<dvs::ShowSettings> smartP; //Smart pointer for auto deleting settings if it will be created bellow via NEW
  if (settings == nullptr) {
    settings = new dvs::ShowSettingsChart();
    smartP.reset(settings);
  }
  if (settings->getVisualType() == dvs::visualizationTypes::CHART)
    res = dvs::showLineChartInBrowser(dblRow, title, static_cast<const dvs::ShowSettingsChart*>(settings));
  return res;
}
//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dvs

#endif //ARRAY_CORE_ARRAY_CORE_H_
