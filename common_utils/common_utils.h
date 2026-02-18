#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "../array_core/configurator.h"
//#START_GRAB_TO_INCLUDES_LIST
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdint.h>
#include <numeric>
#include <stdexcept>
#include <typeinfo>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
enum SEPARATOR_RESULT {
  GOOD_SEPARATOR,
  MORE_THAN_ONE_SEPARATOR,
  NO_SEPARATOR,
  MABE_COMMA_MABE_DOT,
  UNDEFINED_BEHAVIOR
};
using std::string;
using std::vector;

string getCurrentPath();

bool is_file_exists(const string& file_name);

void openFileBySystem(const string& file_name);

bool isPlotlyScriptExists();

bool saveStringToFile(const string& file_name,
                      const string& data);

void mayBeCreateJsWorkingFolder();

void sleepMicroSec(unsigned long microsec);

void openPlotlyHtml(const string& file_name);

bool get_data_from_file(const string& path,
                        vector<std::string>& result);

vector<string> split(const string& target, char c);

bool readMatrix(vector<vector<double>>& outMatrix, const string& path, char dlmtr);


bool make_string(const string& src,
                 const vector<string>& args,
                 string& out);

// Now it doesn't work.
bool deleteFolder(const char* fname);

int find_separator(const std::string& src,
                   char& separator);

//! remove special characters except letters, numbers and '-', '_'. Spaces -> '_'
string removeSpecialCharacters(const string& s);

//! convert this cases to string "null" for Plotly
string nullIfNotFinite(double val);

//! convert vec to string, separated by ","
string vectorToString(const vector<double>& vec);

//! only name
string makeUniqueDavisHtmlName();

//! folder + name + .html
string makeUniqueDavisHtmlRelativePath();

//! sometimes std::to_string reurn str with ',' as separator what is wrong
template <typename T>
string toStringDotSeparator(T data) {
  string str = std::to_string(data);
  std::replace(str.begin(), str.end(), ',', '.');
  return str;
}

//! save to disk vector<T> data
template <typename T>
bool saveVec(const vector<T>& vec, const string& filename, dv::configSaveToDisk config) {
  if (vec.size() == 0) {
    return false;
  }
  std::ofstream fout(filename);
  if (!fout.is_open()) {
    return false;
  }
  size_t rows = vec.size();
  for (int i = 0; i < rows; ++i) {
    fout << vec.at(i) << config.separatorOfRows;
  }
  fout.close();
  return true;
}

//! save to disk vector<vector<T>> data
template <typename T>
bool saveVecVec(const vector<vector<T>>& vecVec, const string& filename, dv::configSaveToDisk config) {
  if (vecVec.size() == 0) {
    return false;
  } else if (vecVec.at(0).size() == 0) {
    return false;
  }

  std::ofstream fout(filename);
  if (!fout.is_open()) {
    return false;
  }
  if (config.isTranspose) {
    size_t rows = vecVec.at(0).size();
    size_t cols = vecVec.size();
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        double val = vecVec.at(j).at(i);
        fout << val;
        if (j < cols - 1) { // we dont need sep at row end
          fout << config.separatorOfCols;
        }
      }
      fout << config.separatorOfRows;
    }
  } else {
    size_t rows = vecVec.size();
    size_t cols = vecVec.at(0).size();
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        double val = vecVec.at(i).at(j);
        fout << val;
        if (j < cols - 1) { // we dont need sep at row end
          fout << config.separatorOfCols;
        }
      }
      fout << config.separatorOfRows;
    }
  }
  fout.close();
  return true;
}

//! convert any container to std::vector with G type
template<typename G,
         typename C, //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = typename std::decay<decltype(*std::begin(std::declval<C>()))>::type,
         typename Enable = typename std::enable_if<std::is_convertible<T, G>::value>::type>
std::vector<G> vecFromTemplate(const C& container) {
  std::vector<G> vec;
  vec.reserve(static_cast<size_t>(std::distance(std::begin(container), std::end(container))));
  for (auto const& v : container) {
    vec.push_back(static_cast<G>(v));
  }
  return vec;
}


bool is_string_convertable_to_digit(const string& sample);


void transponeMatrix(std::vector<std::vector<double>>& matrix);

vector<double> calculateAverageVector(const vector<vector<double>>& vectors);

vector<double> calculateStandardDeviation(const vector<double>& mean,
                                          const vector<vector<double>>& data);

vector<double> doubleAndReverse(const vector<double>& input, const vector<double>& mean);


std::string reverseString(const std::string& input);


template <typename T>
std::vector<std::vector<T>> readBinaryFile(const std::string& filePath,
size_t rowLength) {
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Cannot open file");
  }

  std::vector<std::vector<T>> data;
  std::vector<T> row(rowLength);

  while (file.read(reinterpret_cast<char*>(row.data()), rowLength * sizeof(T))) {
    data.push_back(row);
  }

  // Handle the last row if it's not fully filled
  if (file.gcount() > 0) {
    row.resize(file.gcount() / sizeof(T));
    data.push_back(row);
  }

  file.close();
  return data;
}

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // COMMON_UTILS_COMMON_UTILS_H_
