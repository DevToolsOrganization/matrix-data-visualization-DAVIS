#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "plotly_maker/plotly_maker.h"
#include "ResourceManager/ResourceHandle.h"

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif
    #include <unistd.h>
#endif
std::string getCurrentPath(){
char buffer[1024];
char *answer = getcwd(buffer, sizeof(buffer));
std::string s_cwd;
if (answer)
{
    s_cwd = answer;
}
return s_cwd;
}

#if defined(WIN32) || defined(NT)
void openPlotlyHtml(){
    std::string command = "start ";
    command.append(getCurrentPath());
    command.append("\\example.html");
    system(command.c_str());
}
#elif APPLE
void openPlotlyHtml(){
    std::string command = "open ";
    command.append(getCurrentPath());
    command.append("\\example.html");
    system(command.c_str());
}
#elif linux
void openPlotlyHtml(){
    std::string command = "xdg-open";
    command.append(getCurrentPath());
    command.append("\\example.html");
    system(command.c_str());
}
#else
#error "Unknown compiler"
#endif




inline bool plotly_script_exists () {
    return ( access( "plotly-2.27.0.min.js", F_OK ) != -1 );
}

int main(int argc, char *argv[])
{
    ResourceHandle resource_handle("plotly_maker/plotly-2.27.0.min.js");
    std::cout << "res.txt contents: " << resource_handle.length() <<'\n';
    std::cout << "check plotly script exists: " << plotly_script_exists()<<'\n';
    davis::testPlottyMaker();
    if(!plotly_script_exists()){
        std::ofstream out("plotly-2.27.0.min.js");
        out << resource_handle.c_str();
        out.close();
    }
    openPlotlyHtml();
    return EXIT_SUCCESS;
}


