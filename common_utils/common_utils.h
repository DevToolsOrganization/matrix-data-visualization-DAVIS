#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "string"

namespace davis {


std::string getCurrentPath();

bool isPlotlyScriptExists();

bool saveStringToFile(const std::string& file_name,
                      const std::string& data);

void mayBeCreateJsWorkingFolder();

void sleepMs(unsigned long milisec);

void openPlotlyHtml(const std::string& file_name);

// Now it doesn't work.
bool deleteFolder(const char* fname);

}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
