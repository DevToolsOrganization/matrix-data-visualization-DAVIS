#include <iostream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "ResourceManager/ResourceHandle.h"
#include <cxxopts.hpp>
#include "array_core/array_core.h"
#include "common_utils/common_constants.h"
#include "common_utils/common_utils.h"


int main(int argc, char* argv[]) {
  cxxopts::Options options("davis", "data visualization utility");
  options.add_options()
         ("l,linechart", "linechart values", cxxopts::value<std::string>())
         ("m,heatmap", "heatmap values", cxxopts::value<std::string>())
         ("h,help", "davis commands")
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
  if (result.count("linechart")) {
    auto data = result["linechart"].as<std::string>();
    davis::showLineChartInBrowser(data, "comand_line_linechart", davis::showSettings());
    return EXIT_SUCCESS;
  }
  if (result.count("heatmap")) {
    auto data = result["heatmap"].as<std::string>();
    davis::showHeatMapInBrowser(data, "comand_line_heatmap", davis::showSettings());
    return EXIT_SUCCESS;
  }
  // example how to show values via ArrayCore using PlotlyMaker lib
  std::vector<std::vector<int>> values = {{300, 40, 98, 76}, {99, 45, 20, 1}, {5, 56, 93, 25}, {45, 23, 90, 2}};
  davis::show(values, "values");
  //line chart
  std::vector<double>values2 = {30, 50, 456, 98, 23, 128, 98};
  davis::show(values2, "values2");
  return EXIT_SUCCESS;
}


