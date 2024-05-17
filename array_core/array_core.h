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
bool show(const vector<vector<T>>& data, const string& htmlPageName = dvs::kAppName);

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName);

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName);

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& htmlPageName = dvs::kAppName);

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName = dvs::kAppName);

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& htmlPageName) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (config().common.typeVisual == conf_visualizationTypes::AUTO ||
      config().common.typeVisual == conf_visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName);
  else if (config().common.typeVisual == conf_visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName);
  return res;
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& htmlPageName) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (config().common.typeVisual == conf_visualizationTypes::AUTO ||
      config().common.typeVisual == conf_visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName);
  else if (config().common.typeVisual == conf_visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName);
  return res;
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& htmlPageName) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (config().common.typeVisual == conf_visualizationTypes::AUTO ||
      config().common.typeVisual == conf_visualizationTypes::HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName);
  else if (config().common.typeVisual == conf_visualizationTypes::SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName);
  return res;
}

template <typename T>
bool show(const vector<T>& data, const string& htmlPageName) {
  vector<double> dblRow(data.begin(), data.end());
  bool res = false;
  if (config().common.typeVisual == conf_visualizationTypes::AUTO ||
      config().common.typeVisual == conf_visualizationTypes::CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName);
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  if (config().common.typeVisual == conf_visualizationTypes::AUTO ||
      config().common.typeVisual == conf_visualizationTypes::CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName);
  return res;
}
//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dvs

#endif //ARRAY_CORE_ARRAY_CORE_H_
