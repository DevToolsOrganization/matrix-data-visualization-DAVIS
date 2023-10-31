#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "plotly_maker/plotly_maker.h"
#include "ResourceManager/ResourceHandle.h"
#include "array_core/array_core.h"

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
std::string command = "start ";
#elif APPLE
std::string command = "open ";
#elif linux
std::string command = "xdg-open";
#else
#error "Unknown compiler"
#endif

void openPlotlyHtml(){
    command.append(getCurrentPath());
    command.append("\\example.html");
    system(command.c_str());
}


inline bool plotly_script_exists () {
    return ( access( "plotly-2.27.0.min.js", F_OK ) != -1 );
}

int main(int argc, char *argv[])
{
    ResourceHandle resource_handle("plotly_maker/plotly-2.27.0.min.js");
    std::cout << "res.txt contents: " << resource_handle.length() <<'\n';
    std::cout << "check plotly script exists: " << plotly_script_exists()<<'\n';
    std::string page;
    std::vector<std::vector<double>> values = {{3,40,98,76},{99,45,20,1},{5,56,93,25},{45,23,90,2}};
    davis::show<double>(values);
    if(!davis::createHtmlPageWithPlotlyJS(values, page)){
        std::cout<<"plotly html page was not created....";
        return 0;
    }
    if(!plotly_script_exists()){
        std::ofstream out("plotly-2.27.0.min.js");
        out << resource_handle.c_str();
        out.close();
    }
    // TODO CREATE FILE UTILS for some common operations with files (isExists, Save, Copy .etc)
    std::ofstream out("example.html");
    if(out.is_open()){
        out << page.c_str();
        std::cout<<"Write to file...";
        out.close();
    }else{
        std::cout<<"Unable to open file...";
    }

    openPlotlyHtml();


    return EXIT_SUCCESS;
}


