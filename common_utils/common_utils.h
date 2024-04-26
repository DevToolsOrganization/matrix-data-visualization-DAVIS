#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
//#START_GRAB_TO_INCLUDES_LIST
#include <string>
#include <vector>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace davis {
//#START_GRAB_TO_DAVIS_NAMESPACE
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


// Now it doesn't work.
bool deleteFolder(const char* fname);

//#STOP_GRAB_TO_DAVIS_NAMESPACE
}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
