#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include <string>

namespace dv {
//#START_GRAB_TO_DV_NAMESPACE

enum config_visualizationTypes {
  VISUALTYPE_AUTO, //if user not forces some specific type it will be recognized by context
  VISUALTYPE_CHART,
  VISUALTYPE_HEATMAP
};

enum config_colorscales {
  COLORSCALE_DEFAULT,
  COLORSCALE_SUNNY,
  COLORSCALE_GLAMOUR,
  COLORSCALE_THERMAL,
  COLORSCALE_GRAYSCALE,
  COLORSCALE_YlGnBu,
  COLORSCALE_JET,
  COLORSCALE_HOT,
  COLORSCALE_ELECTRIC,
  COLORSCALE_PORTLAND
};


struct commonSettings {
  commonSettings():
    xLabel("X"),
    yLabel("Y"),
    aspectRatioWidth(1),
    aspectRatioHeight(1),
    isFitPlotToWindow(false) {}
  virtual ~commonSettings() {}
  std::string title;
  std::string xLabel;
  std::string yLabel;
  double aspectRatioWidth; // use it for user scale if isFitPlotToWindow = false
  double aspectRatioHeight;// use it for user scale if isFitPlotToWindow = false
  bool isFitPlotToWindow; //true - plot fits to  browser window, false - square plot
};

struct chartSettings : public commonSettings {
  //currently empty
};

struct heatMapSettings : public commonSettings {
  heatMapSettings():
    colorSc(config_colorscales::COLORSCALE_DEFAULT) {}
  config_colorscales colorSc;
};


struct Config {
  Config():
    typeVisual(VISUALTYPE_AUTO) {}
  void reset() {
    chart = chartSettings();
    heatmap = heatMapSettings();
  }

  chartSettings chart;
  heatMapSettings heatmap;
  config_visualizationTypes typeVisual;
};

struct configSaveToDisk {
  configSaveToDisk():
    separatorOfRows("\n"),
    separatorOfCols(";"),
    isTranspose(false) {}
  std::string separatorOfRows;
  std::string separatorOfCols;
  bool isTranspose; //rows-cols or cols-rows
};



//#STOP_GRAB_TO_DV_NAMESPACE
}// end namespace dv

#endif // CONFIGURATOR_H
