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
  commonSettings(): typeVisual(config_visualizationTypes::VISUALTYPE_AUTO), xLabel("X"), yLabel("Y") {}
  config_visualizationTypes typeVisual;
  std::string title;
  std::string xLabel;
  std::string yLabel;
};

struct chartSettings {

};

struct heatMapSettings {
  heatMapSettings(): colorSc(config_colorscales::COLORSCALE_DEFAULT) {}
  config_colorscales colorSc;
};

struct surfaceSettings {
  surfaceSettings(): colorSc(config_colorscales::COLORSCALE_DEFAULT), zLabel("Z") {}
  config_colorscales colorSc;
  std::string zLabel;
};


class Configurator {
 public:
  static Configurator& getInstance() {
    static Configurator instance;
    return instance;
  }
  Configurator(Configurator const&)   = delete;
  void operator=(Configurator const&) = delete;

  void reset() { //to default settings
    common = commonSettings();
    chart = chartSettings();
    heatmap = heatMapSettings();
    surf = surfaceSettings();
  };

  commonSettings common;
  chartSettings chart;
  heatMapSettings heatmap;
  surfaceSettings surf;

 private:
  Configurator() {};

};

Configurator& config();

//#STOP_GRAB_TO_DV_NAMESPACE
}// end namespace dv

#endif // CONFIGURATOR_H
