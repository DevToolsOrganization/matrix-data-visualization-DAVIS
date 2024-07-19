#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
#include "array_core/array_core.h"
#include "common_utils/common_utils.h"
#include <fstream>
#include <list>
#include <array>

using std::string;
using std::vector;
/*
TEST(ArrayCore, save_to_disk_2d) {
    //! 2-dimensional array
    int rows = 10;
    int cols = 5;
    int** vals2d = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        vals2d[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            vals2d[i][j] = i * cols + j;
        }
    }
    bool result = dv::save(vals2d, rows, cols, "./data/test_saving_save_to_disk_2d.csv");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, save_to_disk_pseudo_2d) {
    //! 1-dimensional array that simulates a 2-dimensional
    int rows = 10;
    int cols = 5;
    int* vals = new int[rows * cols];
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        vals[i * cols + j] = i * cols + j;
      }
    }
    bool result = dv::save(vals, rows, cols, "./data/test_saving_save_to_disk_pseudo_2d.csv");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, save_to_disk_1d) {
    //! 1-dimensional array
    int size = 10;
    int* vals = new int[size];
    for (int i = 0; i < size; ++i) {
        vals[i] = i;
    }
    bool result = dv::save(vals, size,"./data/test_saving_save_to_disk_1d.csv");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, save_to_disk_container1D) {
    //! 1-dimensional container
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool result = dv::save(vec, "./data/test_saving_save_to_disk_container1D.csv");
    EXPECT_EQ(result, true);
}

TEST(ArrayCore, save_to_disk_container2D) {
    //! 2-dimensional container
   int rows = 10;
   int cols = 5;
   vector<vector<double>> arr2;
   for (int i = 0; i < rows; ++i) {
       vector<int> vec(cols);
       for (int j = 0; j < cols; ++j) {
           vec[j] = j;
       }
       arr2.emplace_back(vec);
   }
    bool result = dv::save(arr2, "./data/test_saving_save_to_disk_container2D.csv");
    EXPECT_EQ(result, true);
}
*/
TEST(ArrayCore, universal_1d_conteiner) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  std::list<double> vec = {5, 34};
  bool result = dv::show(vec);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, universal_2d_conteiner) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  std::list<std::list<double>> template2d = {{30.312345, 40, 98, 76}, {-20.12, 45, 20, 1}, {5, 10, 10, 25}, {45, 23, 90, 2}};
  bool result = dv::show(template2d, "testTemplate2d");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, stdArray_of_stdArrays) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  std::array<std::array<double, 5>, 5> arr2;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      arr2.at(i).at(j) = i + j * 3;
    }
  }
  bool result = dv::show(arr2, "stdArray_of_stdArrays");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, configurator) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.312345, 40, 98, 76}, {-20.12, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  auto config = dv::Config();
  config.heatmap.xLabel = "Столбцы";
  config.heatmap.yLabel = "Строки";
  config.heatmap.title = "Тестовая матрица";
  config.heatmap.colorSc = dv::COLORSCALE_GLAMOUR;
  bool result1 = dv::show(values, "HeatMap", config);
  config.typeVisual = dv::VISUALTYPE_SURFACE;
  config.surf.title = "This is Surface!!!";
  bool result2 = dv::show(values, "Surface", config);
  EXPECT_EQ(result1 && result2, true);
}

TEST(ArrayCore, showDefaultSettings) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 400, 400, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  bool result = dv::show(values, "testDefaultSettings");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap1) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  auto config = dv::Config();
  config.heatmap.title = "Black & White TEST MATRIX";
  config.heatmap.colorSc = dv::config_colorscales::COLORSCALE_GRAYSCALE;
  bool result = dv::show(values, "showHeatMap_gray", config);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showSurface) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  auto config = dv::Config();
  config.typeVisual = dv::VISUALTYPE_SURFACE;
  config.surf.xLabel = "xLabel from Settings";
  config.surf.yLabel = "yLabel from Settings";
  config.surf.zLabel = "zLabel from Settings";
  config.surf.title = "Title from Settings";
  config.surf.colorSc = dv::config_colorscales::COLORSCALE_THERMAL;
  bool result = dv::show(values, "showSurface", config);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showPseudo2D) {
  int rows = 5;
  int cols = 3;
  int* vals4 = new int[rows * cols];
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      vals4[i * cols + j] = i * cols + j;
    }
  }
  bool result = dv::show(vals4, rows, cols, "showPseudo2D");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showArray2D) {
  int rows2 = 20;
  int cols2 = 20;
  int** vals5 = new int* [rows2];
  for (int i = 0; i < rows2; ++i) {
    vals5[i] = new int[cols2];
    for (int j = 0; j < cols2; ++j) {
      vals5[i][j] = i * cols2 + j;
    }
  }
  bool result = dv::show(vals5, rows2, cols2);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, testChartDefault) {
  vector<int> vec = {-5, -3, -1, 0, 2, 4, 8, 15, 16};
  bool result = dv::show(vec, "testChartDefault");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showChart) {
  int vals3[] = {2, 6, 4, -34, 56, 33, 2, 15};
  auto config = dv::Config();
  config.chart.title = "Custom title";
  config.chart.xLabel = "Custom xLabel";
  config.chart.yLabel = "Custom yLabel";
  bool result = dv::show(vals3, sizeof(vals3) / sizeof(vals3[0]), "showChart", config);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, readAndShowMatrixFromFile) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values;
  bool readRes = dvs::readMatrix(values, "./data/2023_07_19-12_59_31_379_Baumer2_text.csv", ';');
  EXPECT_EQ(readRes, true);
  bool result = dv::show(values, "readAndShowMatrixFromFile");
  EXPECT_EQ(result, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  std::ignore = RUN_ALL_TESTS();
  return 0;
}
