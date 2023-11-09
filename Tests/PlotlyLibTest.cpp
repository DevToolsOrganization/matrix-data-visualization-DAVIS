#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
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

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    std::ignore = RUN_ALL_TESTS();
    return 0;
}
