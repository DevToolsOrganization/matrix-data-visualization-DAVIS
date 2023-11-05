#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
#include "array_core/array_core.h"
#include "ResourceManager/ResourceHandle.h"
#include "common_utils/common_utils.h"
#include <fstream>
using std::string;


TEST(PlotlyMaker, CreateDefaultHeatMapHtmlPageTest) {

    std::vector<std::vector<double>>testValues = {{43,400,54,980},{200,36,400,55},{120,4,650,5}};
    std::string str_page;
    bool result = davis::createHtmlPageWithPlotlyJS(testValues, str_page);
    std::ofstream out("example.html");
    if(out.is_open()){
        out << str_page.c_str();
        std::cout<<"Write to file...";
        out.close();
    }else{
        std::cout<<"Unable to open file...";
    }
    EXPECT_EQ(result,true);

}

TEST(ArrayCore, showTests){
    EXPECT_EQ(davis::isPlotlyScriptExists(),true);
    //// 1
    std::vector<std::vector<double>> values = {{300.3,40,98,76},{99,45,20,1},{5,56,93,25},{45,23,90,2}};
    bool result = davis::show(values);
    EXPECT_EQ(result,true);
    std::cout<<"test 1"<<std::endl;

//    ////2
//    std::vector<int> vals2 = {2, 6, 4, 34, 56, 33, 2, 1};
//    result = davis::show(vals2);
//    EXPECT_EQ(result,true);
//    std::cout<<"test 2"<<std::endl;

//    ////3
//    int vals3[] = {2, 6, 4, -34, 56, 33, 2, 15};
//    result = davis::show(vals3, sizeof(vals3) / sizeof(vals3[0]));
//    EXPECT_EQ(result,true);
//    std::cout<<"test 3"<<std::endl;

//    ////4
//    int rows = 5; int cols = 3;
//    int *vals4 = new int[rows*cols];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            vals4[i*cols + j] =  i*cols + j;
//        }
//    }
//    result = davis::show(vals4, rows,cols);
//    EXPECT_EQ(result,true);
//    std::cout<<"test 4"<<std::endl;
//    //// 5
//    int rows2 = 20; int cols2 = 20;
//    int** vals5 = new int*[rows2];
//    for (int i = 0; i < rows2; ++i) {
//        vals5[i] = new int[cols2];
//        for (int j = 0; j < cols2; ++j) {
//            vals5[i][j] =  i*cols2 + j;
//        }
//    }
//    result = davis::show(vals5, rows,cols);
//    EXPECT_EQ(result,true);
//    std::cout<<"test 5"<<std::endl;
}



int main(int argc, char* argv[]){
    ResourceHandle resource_handle("res/plotly-2.27.0.min.js");
    if(!davis::isPlotlyScriptExists()){
        davis::saveStringToFile("plotly-2.27.0.min.js",resource_handle.c_str());
    }
    ::testing::InitGoogleTest(&argc, argv);
    std::ignore = RUN_ALL_TESTS();
    return 0;
}
