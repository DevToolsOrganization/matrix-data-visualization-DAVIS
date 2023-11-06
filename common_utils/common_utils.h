#ifndef COMMON_UTILS_COMMON_UTILS_H_
#define COMMON_UTILS_COMMON_UTILS_H_
#include "string"

namespace davis {

//#define GET_VARIABLE_NAME(var) #var //Using: char* var_name= GET_VARIABLE_NAME(var);

//template <typename T>
//std::string getVarName(T var){
//    return std::string(GET_VARIABLE_NAME(var));
//}




inline std::string getVarName( const char* varname)
{
    return std::string(varname);
}
#define GET_VARIABLE_NAME(var) getVarName(#var)

std::string getCurrentPath();
bool isPlotlyScriptExists();
bool saveStringToFile(const std::string &file_name,
                      const std::string &data);
void openPlotlyHtml();
void sleepMs(unsigned long milisec);

}; // namespace davis

#endif // COMMON_UTILS_COMMON_UTILS_H_
