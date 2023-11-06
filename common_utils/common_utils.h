#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "string"

namespace davis {

std::string getCurrentPath();
bool isPlotlyScriptExists();
bool saveStringToFile(const std::string file_name,
                      const std::string &data);
void openPlotlyHtml();
void sleepMs(unsigned long milisec);
}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
