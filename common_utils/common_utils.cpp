#include "common_utils.h"
#include "fstream"
#include "common_constants.h"
#include <sys/stat.h>


namespace{
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif

inline bool is_file_exists (const std::string &file_name) {
    std::ifstream file(file_name.c_str());
    if(!file)return false;
    return true;
}

void openFileBySystem(const std::string &file_name){

    std::string command;
#if defined(WIN32) || defined(NT)
    command = "start ";
#elif APPLE
    command = "open ";
#elif linux
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
#if defined(WIN32) || defined(NT)
    Sleep(milisec);
#elif
    usleep(milisec*1000);
#endif
}

void mayBeCreateJsWorkingFolder(){
    struct stat sb;
    if (stat(kOutFolderName, &sb) != 0)
        mkdir(kOutFolderName);
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
