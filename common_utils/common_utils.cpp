#include "common_utils.h"

namespace{
#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif
    #include <unistd.h>
#endif

inline bool is_file_exists (const std::string &file_name) {
    return ( access( file_name.c_str(), 0 ) != -1 );
}



}

namespace davis {

std::string getCurrentPath(){
    char buffer[1024];
    char *answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;
    if (answer)
    {
        s_cwd = answer;
    }
    return s_cwd;
};

bool isPlotlyScriptExists(){
return is_file_exists("plotly-2.27.0.min.js");
};

void mayBeCopyPlotlyFromResources(){

}

}; // namespace davis
