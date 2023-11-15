#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "string"

namespace davis {

using std::string;

std::string getCurrentPath();

bool isPlotlyScriptExists();

bool saveStringToFile(const string& file_name,
                      const string& data);

void mayBeCreateJsWorkingFolder();

void sleepMs(unsigned long milisec);

void openPlotlyHtml(const string& file_name);

// Now it doesn't work.
bool deleteFolder(const char* fname);

}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
