#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "ResourceManager/ResourceHandle.h"
#include "array_core/array_core.h"
#include "common_utils/common_utils.h"


int main(int argc, char *argv[])
{
    // here we have to copy plotly js to current dir if it doesn't exist
    ResourceHandle resource_handle("plotly_maker/plotly-2.27.0.min.js");
    if(!davis::isPlotlyScriptExists()){
        davis::saveStringToFile("plotly-2.27.0.min.js",resource_handle.c_str());
    }

    // example how to show values via ArrayCore using PlotlyMaker lib
    std::vector<std::vector<int>> values = {{300,40,98,76},{99,45,20,1},{5,56,93,25},{45,23,90,2}};
    davis::show(values);
    davis::sleepMs(2000);

    //line chart
    std::vector<double>values2 = {30,50,456,98,23,128,98};
    davis::show(values2);
    return EXIT_SUCCESS;
}


