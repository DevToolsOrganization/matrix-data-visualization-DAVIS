#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_
//#START_GRAB_TO_INCLUDES_LIST
#include <vector>
#include <iterator>
//#STOP_GRAB_TO_INCLUDES_LIST
#include "plotly_maker/plotly_maker.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"
#include "configurator.h"
#include "multi_plot.h"

namespace dv {
//#START_GRAB_TO_DV_NAMESPACE

using std::vector;
using std::string;


//! (matrix) 2-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template <typename T>
bool save(T** data, uint64_t arrRows, uint64_t arrCols, const string& filename,
          const configSaveToDisk& configuration = configSaveToDisk());

//! (matrix) 1-dimensional array that simulates a 2-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template <typename T>
bool save(const T* data, uint64_t arrRows, uint64_t arrCols, const string& filename,
          const configSaveToDisk& configuration = configSaveToDisk());

//! (chart) 1-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template <typename T>
bool save(const T* data, uint64_t count, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());

//! +(chart) 1-dimensional container
template<typename C,
         typename T = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
bool show(C const& container, const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template<typename C,
         typename T = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
bool save(C const& container, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());


//! +(chart) Two 1-dimensional container for X-Y plot
template<typename C,
         typename T = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
bool show(C const& containerX, C const& containerY, const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template<typename C,
         typename T = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
bool save(C const& containerX, C const& containerY, const string& filename, const configSaveToDisk& configuration = configSaveToDisk());


//! (chart / matrix) 2-dimensional container
template<typename C,
         typename E = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename T = typename std::decay<decltype(*std::begin(std::declval<E>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
bool show(C const& container_of_containers, const string& htmlPageName = dvs::makeUniqueDavisHtmlName(), const Config& configuration = Config());

template<typename C,
         typename E = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename T = typename std::decay<decltype(*std::begin(std::declval<E>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, double>::value>::type>
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
      configuration.typeVisual == VISUALTYPE_HEATMAP) {
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  }
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
      configuration.typeVisual == VISUALTYPE_HEATMAP) {
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  }
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
      configuration.typeVisual == VISUALTYPE_CHART) {
    if (!dvs::isHold) {
      res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
    } else {
      dvs::addTraceBlockToGlobal(dblRow, htmlPageName);
      res = true;
    }
  }
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
      configuration.typeVisual == VISUALTYPE_CHART) {
    if (!dvs::isHold) {
      res = dvs::showLineChartInBrowser(dblRow, htmlPageName, configuration);
    } else {
      dvs::addTraceBlockToGlobal(dblRow, htmlPageName);
      res = true;
    }
  }
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

  bool res = false;
  if (!dvs::isHold) {
    res = dvs::showLineChartInBrowser(dblRowX, dblRowY, htmlPageName, configuration);
  } else {
    dvs::addTraceBlockToGlobal(dblRowX, dblRowY, htmlPageName);
    res = true;
  }
  return res;
}

template<typename C, typename T, typename Enable>
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
  for (const auto& row : container_of_containers) {
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
    vector<double> xVals;
    vector<double> yVals;
    if (size1 == 2) {
      xVals = vecVecDbl[0];
      yVals = vecVecDbl[1];
    } else if (size2 == 2) {
      xVals.reserve(size1);
      for (size_t i = 0; i < size1; ++i) {
        xVals.emplace_back(vecVecDbl[i][0]);
        yVals.emplace_back(vecVecDbl[i][1]);
      }
    }
    if (!dvs::isHold) {
      res = dvs::showLineChartInBrowser(xVals, yVals, htmlPageName, configuration);
    } else {
      dvs::addTraceBlockToGlobal(xVals, yVals, htmlPageName);
      res = true;
    }
  } else if (configuration.typeVisual == VISUALTYPE_AUTO ||
             configuration.typeVisual == VISUALTYPE_HEATMAP) {
    res = dvs::showHeatMapInBrowser(vecVecDbl, htmlPageName, configuration);
  }
  return res;
}

template<typename C, typename E, typename T, typename Enable>
bool save(C const& container_of_containers, const string& filename, const configSaveToDisk& configuration) {
  vector<vector<T>> vecVec;
  vecVec.reserve(container_of_containers.size());
  for (const auto& row : container_of_containers) {
    vector<T> rowTemp = dvs::vecFromTemplate<T>(row);
    vecVec.emplace_back(rowTemp);
  }
  bool res = dvs::saveVecVec<T>(vecVec, filename, configuration);
  return res;
}

//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dv

#endif //ARRAY_CORE_ARRAY_CORE_H_
