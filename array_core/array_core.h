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
          std::unique_ptr<ShowSettings> settings = std::make_unique<ShowSettingsHeatMap>());

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName,  std::unique_ptr<ShowSettings> settings = std::make_unique<ShowSettingsHeatMap>());

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName,  std::unique_ptr<ShowSettings> settings = std::make_unique<ShowSettingsHeatMap>());

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& title = kAppName,
          std::unique_ptr<ShowSettings> settings = std::make_unique<ShowSettingsChart>());

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& title = kAppName,
          std::unique_ptr<ShowSettings> settings = std::make_unique<ShowSettingsChart>());

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& title,
          std::unique_ptr<ShowSettings> settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings.get()));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings.get()));
  return res;
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& title,
          std::unique_ptr<ShowSettings> settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings.get()));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings.get()));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& title,
          std::unique_ptr<ShowSettings> settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (settings->visualType == davis::visualizationTypes::HEATMAP)
    res = davis::showHeatMapInBrowser(vecVecDbl, title, static_cast<const ShowSettingsHeatMap*>(settings.get()));
  else if (settings->visualType == davis::visualizationTypes::SURFACE)
    res = davis::showSurfaceInBrowser(vecVecDbl, title, static_cast<const ShowSettingsSurface*>(settings.get()));
  return res;
}

template <typename T>
bool show(const vector<T>& data, const string& title,
          std::unique_ptr<ShowSettings> settings) {
  vector<double> dblRow(data.begin(), data.end());
  bool res = false;
  if (settings->visualType == davis::visualizationTypes::CHART)
    res = davis::showLineChartInBrowser(dblRow, title, static_cast<const ShowSettingsChart*>(settings.get()));
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& title,
          std::unique_ptr<ShowSettings> settings) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  if (settings->visualType == davis::visualizationTypes::CHART)
    res = davis::showLineChartInBrowser(dblRow, title, static_cast<const ShowSettingsChart*>(settings.get()));
  return res;
}

} // namespace davis

#endif //ARRAY_CORE_ARRAY_CORE_H_
