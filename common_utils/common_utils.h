#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "../array_core/configurator.h"
//#START_GRAB_TO_INCLUDES_LIST
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
enum SEPARATOR_RESULT {
  GOOD_SEPARATOR,
  MORE_THAN_ONE_SEPARATOR,
  NO_SEPARATOR,
  MABE_COMMA_MABE_DOT,
  UNDEFINED_BEHAVIOR,
  EMPTY_LINE
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

void sleepMs(unsigned long milisec);

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
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
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
         typename C,    //https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>>>
vector<G> vecFromTemplate(const C& container) {
  vector<G> vec(container.size());
  uint64_t i = 0;
  for (auto v : container) {
    vec[i] = static_cast<G>(v);
    ++i;
  }
  return vec;
}

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // COMMON_UTILS_COMMON_UTILS_H_
