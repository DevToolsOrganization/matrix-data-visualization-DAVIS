#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include "plotly_maker/plotly_maker.h"
#include "ResourceManager/ResourceHandle.h"

inline bool plotly_script_exists () {
    return ( access( "plotly-2.27.0.min.js", F_OK ) != -1 );
}

int main(int argc, char *argv[])
{
    ResourceHandle resource_handle("plotly_maker/plotly-2.27.0.min.js");
    std::cout << "res.txt contents: " << resource_handle.length() <<'\n';
    std::cout << "plotly script exists: " << plotly_script_exists();
    davis::testPlottyMaker();
    if(!plotly_script_exists()){
    std::ofstream out("plotly-2.27.0.min.js");
    out << resource_handle.c_str();
    out.close();
    }
    return EXIT_SUCCESS;
}


