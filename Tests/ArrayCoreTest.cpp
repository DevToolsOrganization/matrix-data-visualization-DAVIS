#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
#include "array_core/array_core.h"
#include "common_utils/common_utils.h"
#include <fstream>

using std::string;

TEST(ArrayCore, showHeatMap1) {
    EXPECT_EQ(davis::isPlotlyScriptExists(), true);
    std::vector<std::vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
    bool result = davis::show(values, "test1");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap2) {
// davis::sleepMs(1000);
    std::vector<int> vals2 = {2, 6, 4, 34, 56, 33, 2, 1};
    bool result = davis::show(vals2, "test2");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap3) {
// davis::sleepMs(1000);
    int vals3[] = {2, 6, 4, -34, 56, 33, 2, 15};
    bool result = davis::show(vals3, sizeof(vals3) / sizeof(vals3[0]), "test3");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap4) {
// davis::sleepMs(1000);
    int rows = 5;
    int cols = 3;
    int* vals4 = new int[rows * cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            vals4[i * cols + j] = i * cols + j;
        }
    }
    bool result = davis::show(vals4, rows, cols, "test4");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap5) {
// davis::sleepMs(1000);
    int rows2 = 20;
    int cols2 = 20;
    int** vals5 = new int* [rows2];
    for (int i = 0; i < rows2; ++i) {
        vals5[i] = new int[cols2];
        for (int j = 0; j < cols2; ++j) {
            vals5[i][j] = i * cols2 + j;
        }
    }
    bool result = davis::show(vals5, rows2, cols2);
    EXPECT_EQ(result, true);
}


int main(int argc, char* argv[]) {
    //std::cout<< std::endl << davis::deleteFolder(davis::saveFolderName) << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    std::ignore = RUN_ALL_TESTS();
    return 0;
}
