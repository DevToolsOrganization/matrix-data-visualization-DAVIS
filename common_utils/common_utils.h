#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
//#START_GRAB_TO_INCLUDES_LIST
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace dvs {
//#START_GRAB_TO_NAMESPACE
using std::string;
using std::vector;

string getCurrentPath();

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
                 vector<string>& args,
                 string& out);

// Now it doesn't work.
bool deleteFolder(const char* fname);

//#STOP_GRAB_TO_NAMESPACE
}; // namespace dvs

#endif // COMMON_UTILS_COMMON_UTILS_H_
