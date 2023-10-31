#ifndef ARRAY_CORE_ARRAY_CORE_H_
#define ARRAY_CORE_ARRAY_CORE_H_

#include <iostream>
#include <vector>
#include "plotly_maker/plotly_maker.h"

namespace davis {

bool generateAndShowHtml(std::vector<std::vector<double>> array);


template <typename T>
void show(std::vector<std::vector<T>> array);

template <typename T>
void show(std::vector<T> array);

//! two-dimensional array
template <typename T>
void show(T **array, uint64_t arrRows, uint64_t arrCols);

//! A one-dimensional array that simulates a two-dimensional one (element access [i*cols+j])
template <typename T>
void show(T **array, uint64_t arrRows, uint64_t arrCols);

//! two-dimensional array
template <typename T>
void show(T *array, uint64_t size);

template <typename T>
void show(std::vector<std::vector<T>> array){
    std::cout<< "show"<<std::endl;
}

} // namespace davis




#endif //ARRAY_CORE_ARRAY_CORE_H_
