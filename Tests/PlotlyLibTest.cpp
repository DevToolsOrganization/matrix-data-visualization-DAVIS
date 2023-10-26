#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
using std::string;

class PlotlyMaker{

};

TEST(PlotlyMaker, launchCase) {
	
    bool result = davis::testPlottyMaker();
	EXPECT_EQ(result,true);

}

int main(int argc, char* argv[]){

	::testing::InitGoogleTest(&argc, argv);
    std::ignore = RUN_ALL_TESTS();
    char exit;
    std::cin >> exit;
	return 0;
}
