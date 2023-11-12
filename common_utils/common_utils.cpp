#include "common_utils.h"
#include "fstream"
#include "common_constants.h"
#include <sys/stat.h>


namespace{
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif __linux__
#include <unistd.h>
#endif

inline bool is_file_exists (const std::string &file_name) {
    std::ifstream file(file_name.c_str());
    if(!file)return false;
    return true;
}

void openFileBySystem(const std::string &file_name){

    std::string command;
#ifdef _WIN32
    command = "start ";
#elif __APPLE__
    command = "open ";
#elif __linux__
    command = "xdg-open ";
#else
#error "Unknown compiler"
#endif
    command.append(file_name);
    system(command.c_str());
}

} // namespace

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
    return is_file_exists(kPlotlyJsWorkPath);
};

bool saveStringToFile(const std::string &file_name,
                      const std::string &data){
    std::ofstream out(file_name);
    if(out.is_open()){
        out << data.c_str();
        out.close();
        return true;
    }
    return false;
}


void openPlotlyHtml(const std::string &file_name){
    openFileBySystem(file_name);
}

void sleepMs(unsigned long milisec)
{
#ifdef _WIN32
    Sleep(milisec);
#elif __linux__
    usleep(milisec*1000);
#endif
}

void mayBeCreateJsWorkingFolder(){
    struct stat sb;
    if (stat(kOutFolderName, &sb) != 0){
        #ifdef _WIN32
        mkdir(kOutFolderName);
        #elif __linux__
        mode_t mode = 0755;
        mkdir(kOutFolderName,mode);
        #endif
    }
}

bool deleteFolder(const char* fname)
{
    struct stat sb;

    if (stat(fname, &sb) == 0){

        //rmdir(fname);
        return true;
    }
    else{
        return false;
    }

}

}; // namespace davis
