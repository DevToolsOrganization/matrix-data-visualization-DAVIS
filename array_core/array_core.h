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


template <typename T>
struct is_cont {
  static const bool value = false;
};

template <typename T,typename Alloc>
struct is_cont<std::vector<T,Alloc> > {
  static const bool value = true;
};



using std::vector;
using std::string;


//! two-dimensional vector
template <typename T>
bool show(const vector<vector<T>>& data, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());


/*
template<typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
    typename T = std::decay_t<
        decltype(*begin(std::declval<C>()))>,
    typename = std::enable_if_t<
        std::is_convertible_v<T, int>>>
*/


template<typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
    typename T = std::decay_t<
        decltype(*begin(std::declval<C>()))>,
    typename = std::enable_if_t<
        std::is_convertible_v<T, double>>>
auto show(C const& container, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config())
{

  vector<double> dblRow(container.size());
  int i = 0;
  for (auto v : container) {
    dblRow[i] = v;
    ++i;
  }
  bool res = false;
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
  return res;
}

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& htmlPageName, const Config& configuration) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_HEATMAP) {
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  } else if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
  return res;
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& htmlPageName, const Config& configuration) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (uint64_t i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  bool res = false;
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  else if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
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
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_HEATMAP)
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  else if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_SURFACE)
    res = dvs::showSurfaceInBrowser(vecVecDbl, htmlPageName, configuration);
  return res;
}

template <typename T>
bool show(const vector<T>& data, const string& htmlPageName, const Config& configuration) {
  vector<double> dblRow(data.begin(), data.end());
  bool res = false;
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
  return res;
}

template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName, const Config& configuration) {
  vector<double> dblRow(data, data + count);
  bool res = false;
  if (configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_AUTO ||
      configuration.common.typeVisual == config_visualizationTypes::VISUALTYPE_CHART)
    res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
  return res;
}
//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dvs

#endif //ARRAY_CORE_ARRAY_CORE_H_
