#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_

#include <iostream>
#include <vector>
#include "plotly_maker/plotly_maker.h"
#include "common_utils/common_utils.h"

namespace davis {
using std::vector;

enum class visualizationTypes{
    graph, heatmap, surface
};

enum class colorscales{
    gray, rainbow
};

struct showSettings{
    visualizationTypes visualType = visualizationTypes::heatmap;
    colorscales colorscale = colorscales::rainbow;
};


//! two-dimensional vector
template <typename T>
bool show(const vector<vector<T>> &data, std::string title = "data");

//! one-dimensional vector
template <typename T>
bool show(const vector<T> &data, std::string title = "data");

//! two-dimensional array
template <typename T>
bool show(T **data, uint64_t arrRows, uint64_t arrCols, std::string title = "data");

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T *data, uint64_t arrRows, uint64_t arrCols, std::string title = "data");

//! one-dimensional array
template <typename T>
bool show(const T *data, uint64_t count, std::string title = "data");

// *******************************
// template functions realisations:
// *******************************

template <typename T>
bool show(const vector<vector<T>> &data, std::string title)
{
    vector<vector<double>> vecVecDbl;
    vecVecDbl.reserve(data.size());
    for (vector<T> row : data) {
        vector<double> dblRow(row.begin(), row.end());
        vecVecDbl.emplace_back(dblRow);
    }
    return davis::showHeatMapInBrowser(vecVecDbl);

}

template <typename T>
bool show(const vector<T> &data, std::string title)
{
    vector<double> dblRow(data.begin(), data.end());
    return davis::showLineChartInBrowser(dblRow);
}

template <typename T>
bool show(T **data, uint64_t arrRows, uint64_t arrCols, std::string title)
{
    vector<vector<double>> vecVecDbl;
    vecVecDbl.reserve(arrRows);
    for (int i = 0; i < arrRows; ++i) {
        vector<double> dblRow(&data[i][0], &data[i][0] + arrCols);
        vecVecDbl.emplace_back(dblRow);
    }
    return davis::showHeatMapInBrowser(vecVecDbl);
}

template <typename T>
bool show(const T *data, uint64_t arrRows, uint64_t arrCols, std::string title)
{
    vector<vector<double>> vecVecDbl;
    vecVecDbl.reserve(arrRows);
    for (int i = 0; i < arrRows; ++i) {
        vector<double> dblRow(&data[i*arrCols], &data[i*arrCols] + arrCols);
        vecVecDbl.emplace_back(dblRow);
    }
    return davis::showHeatMapInBrowser(vecVecDbl);
}

template <typename T>
bool show(const T *data, uint64_t count, std::string title)
{
    vector<double> dblRow(data, data + count);
    return davis::showLineChartInBrowser(dblRow);
}

} // namespace davis





#endif //ARRAY_CORE_ARRAY_CORE_H_
