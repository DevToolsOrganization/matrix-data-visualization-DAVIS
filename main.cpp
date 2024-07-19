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
         ("f,file", "path to input file", cxxopts::value<std::string>())
         ("t,charttype", "chart type", cxxopts::value<std::string>())
         ;
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  // here we have to copy plotly js to current dir if it doesn't exist
  ResourceHandle resource_handle(dvs::kPlotlyJsResourcePath);
  if (!dvs::isPlotlyScriptExists()) {
    dvs::mayBeCreateJsWorkingFolder();
    dvs::saveStringToFile(dvs::kPlotlyJsWorkPath, resource_handle.c_str());
  }

  auto config = dv::Config();

  if (result.count("linechart")) {
    auto data = result["linechart"].as<std::string>();
    config.typeVisual = dv::VISUALTYPE_CHART;
    dvs::showLineChartInBrowser(data, "comand_line_linechart", config);
    return EXIT_SUCCESS;
  } else if (result.count("heatmap")) {
    auto data = result["heatmap"].as<std::string>();
    config.typeVisual = dv::VISUALTYPE_HEATMAP;
    dvs::showHeatMapInBrowser(data, "comand_line_heatmap", config);
    return EXIT_SUCCESS;
  } else if (result.count("surface")) {
    config.typeVisual = dv::VISUALTYPE_SURFACE;
    auto data = result["surface"].as<std::string>();
    dvs::showSurfaceInBrowser(data, "comand_line_surface", config);
    return EXIT_SUCCESS;
  } else if (result.count("file")) {
    auto data_path = result["file"].as<std::string>();
    std::vector<vector<double>> data;
    if (dvs::readMatrix(data, data_path, ';')) {
      if (data.size() == 1) {
        config.typeVisual = dv::VISUALTYPE_CHART;
        dv::show(data[0], "file_line_chart", config);
      } else {
        dv::show(data);
      }
    }
  }

  return EXIT_SUCCESS;
}


