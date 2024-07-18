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

bool getDataFromFile(const string& path, string& result);

vector<string> split(const string& target, char c);

bool readMatrix(vector<vector<double>>& outMatrix, const string& path, char dlmtr);


bool make_string(const string& src,
                 const vector<string>& args,
                 string& out);

// Now it doesn't work.
bool deleteFolder(const char* fname);

//! save to disk vector<vector<T>> data
template <typename T>
bool saveVecVec(const vector<vector<T>>& vecVec,const string& filename, dv::configSaveToDisk config);

template <typename T>
bool saveVecVec(const vector<vector<T>>& vecVec,const string& filename, dv::configSaveToDisk config)
{
    if(vecVec.size() == 0){
        return false;
    }else if(vecVec.at(0).size() == 0){
        return false;
    }

    std::ofstream fout(filename);
    if(!fout.is_open()){
        return false;
    }
    size_t rows = vecVec.size();
    size_t cols = vecVec.at(0).size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j){
            fout << vecVec.at(i).at(j) << config.separatorOfCols;
        }
        fout << config.separatorOfRows;
    }
    fout.close();
    return true;
}


//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // COMMON_UTILS_COMMON_UTILS_H_
