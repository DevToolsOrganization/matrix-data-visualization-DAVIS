#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "ResourceManager/ResourceHandle.h"
#include <cxxopts.hpp>
#include "array_core/array_core.h"
#include "common_utils/common_constants.h"
#include "common_utils/common_utils.h"

using std::vector;

int main(int argc, char* argv[]) {
  cxxopts::Options options("davis", "data visualization utility");
  options.add_options()
         ("h,help", "davis commands")
         ("l,linechart", "linechart values", cxxopts::value<std::string>())
         ("m,heatmap", "heatmap values", cxxopts::value<std::string>())
         ("s,surface", "surface values", cxxopts::value<std::string>())
         ("f,datapath", "path to data", cxxopts::value<std::string>())
         ("t,charttype", "chart type", cxxopts::value<std::string>())
         ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  // here we have to copy plotly js to current dir if it doesn't exist
  ResourceHandle resource_handle(davis::kPlotlyJsResourcePath);
  if (!davis::isPlotlyScriptExists()) {
    davis::mayBeCreateJsWorkingFolder();
    davis::saveStringToFile(davis::kPlotlyJsWorkPath, resource_handle.c_str());
  }


  vector<vector<double>> values = {{30.3, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  auto setHeatM = davis::createShowSettingsHeatMap();
  setHeatM->colorScale = davis::colorscales::GLAMOUR;
  davis::show(values, "testHeat1", setHeatM.get());

  if (result.count("linechart")) {
    auto data = result["linechart"].as<std::string>();
    auto set = davis::createShowSettingsChart();
    davis::showLineChartInBrowser(data, "comand_line_linechart", set.get());
    return EXIT_SUCCESS;
  } else if (result.count("heatmap")) {
    auto data = result["heatmap"].as<std::string>();
    auto set = davis::createShowSettingsHeatMap();
    davis::showHeatMapInBrowser(data, "comand_line_heatmap", set.get());
    return EXIT_SUCCESS;
  } else if (result.count("surface")) {
    auto data = result["surface"].as<std::string>();
    auto settings = davis::createShowSettingsSurface();
    settings->colorScale = davis::colorscales::GLAMOUR;
    davis::showSurfaceInBrowser(data, "comand_line_surface", settings.get());
    return EXIT_SUCCESS;
  } else if (result.count("datapath")) {
    auto data_path = result["datapath"].as<std::string>();
    std::string str_data;
    if (davis::getDataFromFile(data_path, str_data)) {
      if (result.count("charttype")) {
        auto chart_type = result["charttype"].as<std::string>();
        if (chart_type == "l" || chart_type == "linechart") {
          auto settings = davis::createShowSettingsChart();
          davis::showLineChartInBrowser(str_data, "file_data", settings.get());
        } else if (chart_type == "s" || chart_type == "surface") {
          auto settings = davis::createShowSettingsSurface();
          settings->colorScale = davis::colorscales::GLAMOUR;
          davis::showSurfaceInBrowser(str_data, "surface", settings.get());
        } else if (chart_type == "m" || chart_type == "heatmap") {

        }
      } else {
        auto settings = davis::createShowSettingsHeatMap();
        davis::showHeatMapInBrowser(str_data, "file_data", settings.get());
      }
    }
  }
  return EXIT_SUCCESS;
}


