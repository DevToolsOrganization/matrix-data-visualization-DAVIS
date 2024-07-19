#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include <string>

namespace dv {
//#START_GRAB_TO_DV_NAMESPACE

enum config_visualizationTypes {
  VISUALTYPE_AUTO, //if user not forces some specific type it will be recognized by context
  VISUALTYPE_CHART,
  VISUALTYPE_HEATMAP,
  VISUALTYPE_SURFACE
};

enum config_colorscales {
  COLORSCALE_DEFAULT,
  COLORSCALE_SUNNY,
  COLORSCALE_GLAMOUR,
  COLORSCALE_THERMAL,
  COLORSCALE_GRAYSCALE
};


struct commonSettings {
  commonSettings():
    xLabel("X"),
    yLabel("Y") {}
  virtual ~commonSettings() {}
  std::string title;
  std::string xLabel;
  std::string yLabel;
};

struct chartSettings : public commonSettings {
  //currently empty
};

struct heatMapSettings : public commonSettings {
  heatMapSettings():
    colorSc(config_colorscales::COLORSCALE_DEFAULT) {}
  config_colorscales colorSc;
};

struct surfaceSettings : public commonSettings {
  surfaceSettings():
    colorSc(config_colorscales::COLORSCALE_DEFAULT),
    zLabel("Z") {}
  config_colorscales colorSc;
  std::string zLabel;
};


struct Config {
  Config():
    typeVisual(VISUALTYPE_AUTO) {}
  void reset() {
    chart = chartSettings();
    heatmap = heatMapSettings();
    surf = surfaceSettings();
  }

  chartSettings chart;
  heatMapSettings heatmap;
  surfaceSettings surf;

  config_visualizationTypes typeVisual;
};

struct configSaveToDisk {
  configSaveToDisk():
    separatorOfRows("\n"),
    separatorOfCols(";") {}
  std::string separatorOfRows;
  std::string separatorOfCols;
};



//#STOP_GRAB_TO_DV_NAMESPACE
}// end namespace dv

#endif // CONFIGURATOR_H
