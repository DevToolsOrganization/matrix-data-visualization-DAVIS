#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "plotly_maker/plotly_maker.h"
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

    //// 1
        std::vector<std::vector<double>> values = {{300.3,40,98,76},{99,45,20,1},{5,56,93,25},{45,23,90,2}};
        davis::show(values);

     ////2
//    std::vector<int> vals2 = {2, 6, 4, 34, 56, 33, 2, 1};
//    davis::show(vals2);

    ////3
//    int vals3[] = {2, 6, 4, -34, 56, 33, 2, 15};
//    davis::show(vals3, sizeof(vals3) / sizeof(vals3[0]));

    ////4
//    int rows = 5; int cols = 3;
//    int *vals4 = new int[rows*cols];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            vals4[i*cols + j] =  i*cols + j;
//        }
//    }
//    davis::show(vals4, rows,cols);

    //// 5
//    int rows = 20; int cols = 20;
//    int** vals5 = new int*[rows];
//    for (int i = 0; i < rows; ++i) {
//        vals5[i] = new int[cols];
//        for (int j = 0; j < cols; ++j) {
//            vals5[i][j] =  i*cols + j;
//        }
//    }
//    davis::show(vals5, rows,cols);

    return EXIT_SUCCESS;
}


