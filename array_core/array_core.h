#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_

#include <iostream>
#include <vector>
#include "plotly_maker/plotly_maker.h"
#include "utils_core.h"

using std::vector;


namespace davis {

enum class dataType{
    ptr1D, ptr2D, ptrPseudo2D, vector2D, vector1D
};

bool generateAndShowHtml(const vector<vector<double>> &data);

//! two-dimensional vector
template <typename T>
void show(const vector<vector<T>> &data);

//! one-dimensional vector
template <typename T>
void show(const vector<T> &data);

//! two-dimensional array
template <typename T>
void show(const T **data, uint64_t arrRows, uint64_t arrCols);

//! a one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
void show(const T *data, uint64_t arrRows, uint64_t arrCols);

//! one-dimensional array
template <typename T>
void show(const T *data);

// *******************************
// template functions realisations:
// *******************************

template <typename T>
void show(const vector<vector<T>> &data)
{
    dataType type = dataType::vector2D;
    vector<vector<double>> vecVecDbl;
    vecVecDbl.reserve(data.size());
    for (vector<T> row : data) {
        vector<double> dblRow(row.begin(), row.end());
        vecVecDbl.push_back(dblRow);
    }
}

template <typename T>
void show(const vector<T> &data)
{
    dataType type = dataType::vector1D;
    vector<double> dblRow(data.begin(), data.end());

}

template <typename T>
void show(const T **data, uint64_t arrRows, uint64_t arrCols)
{
    dataType type = dataType::ptr2D;
    //TODO
}

template <typename T>
void show(const T *data, uint64_t arrRows, uint64_t arrCols)
{
    dataType type = dataType::ptrPseudo2D;
    //TODO
}

template <typename T>
void show(const T *data, uint64_t count)
{
    dataType type = dataType::ptr1D;
    vector<double> values(data, data + count);

}

} // namespace davis





#endif //ARRAY_CORE_ARRAY_CORE_H_
