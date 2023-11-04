#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "string"

namespace davis {

std::string getCurrentPath();
bool isPlotlyScriptExists();
void mayBeCopyPlotlyFromResources();

}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
