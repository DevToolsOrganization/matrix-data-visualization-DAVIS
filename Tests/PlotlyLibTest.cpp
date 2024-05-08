#include "gtest/gtest.h"
#include "plotly_maker/plotly_maker.h"
#include <fstream>
using std::string;


TEST(PlotlyMaker, CreateDefaultHeatMapHtmlPageTest) {
  std::vector<std::vector<double>>testValues = {{43, 400, 54, 980}, {200, 36, 400, 55}, {120, 4, 650, 5}};
  std::string str_page = "test_page";
  bool result = dvs::createHtmlPageWithPlotlyJS(testValues, str_page, dvs::visualizationTypes::HEATMAP, dvs::colorscales::GLAMOUR);
  std::ofstream out("example.html");
  if (out.is_open()) {
    out << str_page.c_str();
    std::cout << "Write to file...";
    out.close();
  } else {
    std::cout << "Unable to open file...";
  }
  EXPECT_EQ(result, true);
}

TEST(PlotlyMaker, ShowGlamourHeatMapHtmlPageTest) {
  std::vector<std::vector<double>>testValues = {{43, 400, 54, 980}, {200, 36, 400, 55}, {120, 4, 650, 5}};
  std::string str_page = "veryGlamourPage";
  auto settings = std::make_unique<dvs::ShowSettingsHeatMap>(dvs::colorscales::GLAMOUR);
  bool result = dvs::showHeatMapInBrowser(testValues, str_page, settings.get());
  EXPECT_EQ(result, true);
}

TEST(PlotlyMaker, ShowThermalHeatMapHtmlPageTest) {
  std::vector<std::vector<double>>testValues = {{43, 400, 54, 980}, {200, 36, 400, 55}, {120, 4, 650, 5}};
  std::string str_page = "veryHotPage";
  auto settings = std::make_unique<dvs::ShowSettingsHeatMap>(dvs::colorscales::THERMAL);
  bool result = dvs::showHeatMapInBrowser(testValues, str_page, settings.get());
  EXPECT_EQ(result, true);
}

TEST(PlotlyMaker, ShowSunnyHeatMapHtmlPageTest) {
  std::vector<std::vector<double>>testValues = {{43, 400, 54, 980}, {200, 36, 400, 55}, {120, 4, 650, 5}};
  std::string str_page = "SunnyPage";
  auto settings = std::make_unique<dvs::ShowSettingsHeatMap>(dvs::colorscales::SUNNY);
  bool result = dvs::showHeatMapInBrowser(testValues, str_page, settings.get());
  EXPECT_EQ(result, true);
}

TEST(PlotlyMaker, ShowThermalSurfaceHtmlPageTest) {
  std::vector<std::vector<double>>testValues = {{43, 400, 54, 980}, {200, 36, 400, 55}, {120, 4, 650, 5}};
  std::string str_page = "ThermalSurfacePage";
  auto settings = std::make_unique<dvs::ShowSettingsSurface>(dvs::colorscales::THERMAL);
  bool result = dvs::showSurfaceInBrowser(testValues, str_page, settings.get());
  EXPECT_EQ(result, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  std::ignore = RUN_ALL_TESTS();
  return 0;
}
