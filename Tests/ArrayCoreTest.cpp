#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
#include "array_core/array_core.h"
#include "common_utils/common_utils.h"
#include <fstream>

using std::string;
using std::vector;

TEST(ArrayCore, configurator) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.312345, 40, 98, 76}, {-20.12, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  dv::config().reset();
  dv::commonSettings comS;
  comS.xLabel = "Столбцы";
  comS.yLabel = "Строки";
  comS.title = "Тестовая матрица";
  dv::config().common = comS;
  dv::config().heatmap.colorSc = dv::COLORSCALE_GLAMOUR;
  bool result1 = dv::show(values, "HeatMap");
  dv::config().common.typeVisual = dv::VISUALTYPE_SURFACE;
  bool result2 = dv::show(values, "Surface");
  EXPECT_EQ(result1 && result2, true);
}

TEST(ArrayCore, showDefaultSettings) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 400, 400, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  dv::config().reset();
  bool result = dv::show(values, "testDefaultSettings");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showHeatMap1) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  dv::config().reset();
  dv::config().common.title = "Black & White TEST MATRIX";
  dv::config().heatmap.colorSc = dv::config_colorscales::COLORSCALE_GRAYSCALE;
  bool result = dv::show(values, "showHeatMap_gray");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showSurface1) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  dv::config().reset();
  dv::config().common.typeVisual = dv::VISUALTYPE_SURFACE;
  bool result = dv::show(values, "showSurface1");
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
  dv::config().reset();
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
  dv::config().reset();
  bool result = dv::show(vals5, rows2, cols2);
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, testChartDefault) {
  vector<int> vec = {-5, -3, -1, 0, 2, 4, 8, 15, 16};
  dv::config().reset();
  bool result = dv::show(vec, "testChartDefault");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, showChart) {
  int vals3[] = {2, 6, 4, -34, 56, 33, 2, 15};
  dv::config().reset();
  bool result = dv::show(vals3, sizeof(vals3) / sizeof(vals3[0]), "showChart");
  EXPECT_EQ(result, true);
}

TEST(ArrayCore, readAndShowMatrixFromFile) {
  EXPECT_EQ(dvs::isPlotlyScriptExists(), true);
  vector<vector<double>> values;
  bool readRes = dvs::readMatrix(values, "./data/2023_07_19-12_59_31_379_Baumer2_text.csv", ';');
  EXPECT_EQ(readRes, true);
  dv::config().reset();
  bool result = dv::show(values, "readAndShowMatrixFromFile");
  EXPECT_EQ(result, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  std::ignore = RUN_ALL_TESTS();
  return 0;
}
