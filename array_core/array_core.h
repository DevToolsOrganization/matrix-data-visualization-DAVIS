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
          const showSettings& settings = showSettings());

//! one-dimensional vector
template <typename T>
bool show(const vector<T>& data, const string& title = kAppName,
          const showSettings& settings = showSettings());

//! two-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName, const showSettings& settings = showSettings());

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& title = kAppName, const showSettings& settings = showSettings());

//! one-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& title = kAppName,
          const showSettings& settings = showSettings());

// ***********************************
// template functions implementations:
// ***********************************

template <typename T>
bool show(const vector<vector<T>>& data, const string& title,
          const showSettings& settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(data.size());
  for (vector<T> row : data) {
    vector<double> dblRow(row.begin(), row.end());
    vecVecDbl.emplace_back(dblRow);
  }
  return davis::showHeatMapInBrowser(vecVecDbl, title, settings);
}

template <typename T>
bool show(const vector<T>& data, const string& title,
          const showSettings& settings) {
  vector<double> dblRow(data.begin(), data.end());
  return davis::showLineChartInBrowser(dblRow, title, settings);
}

template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols, const string& title,
          const showSettings& settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (int i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  return davis::showHeatMapInBrowser(vecVecDbl, title, settings);
}

template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols, const string& title,
          const showSettings& settings) {
  vector<vector<double>> vecVecDbl;
  vecVecDbl.reserve(arrRows);
  for (int i = 0; i < arrRows; ++i) {
    vector<double> dblRow(&data[i * arrCols], &data[i * arrCols] + arrCols);
    vecVecDbl.emplace_back(dblRow);
  }
  return davis::showHeatMapInBrowser(vecVecDbl, title, settings);
}

template <typename T>
bool show(const T* data, uint64_t count, const string& title,
          const showSettings& settings) {
  vector<double> dblRow(data, data + count);
  return davis::showLineChartInBrowser(dblRow, title, settings);
}

} // namespace davis

#endif //ARRAY_CORE_ARRAY_CORE_H_
