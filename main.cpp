#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "plotly_maker/plotly_maker.h"
#include "ResourceManager/ResourceHandle.h"
#include "arrayCore/arrayCore.h"
#include "common_utils/common_utils.h"


int main(int argc, char *argv[])
{
    // here we have to copy plotly js to current dir if it doesn't exist
    ResourceHandle resource_handle("plotly_maker/plotly-2.27.0.min.js");
    if(!davis::isPlotlyScriptExists()){
        davis::saveStringToFile("plotly-2.27.0.min.js",resource_handle.c_str());
    }

    // example how to show values using PlotlyMaker lib
    std::vector<std::vector<double>> values = {{300,40,98,76},{99,45,20,1},{5,56,93,25},{45,23,90,2}};
    davis::showDataInBrowser(values);
    return EXIT_SUCCESS;
}


