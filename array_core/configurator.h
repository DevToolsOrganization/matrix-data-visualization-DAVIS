#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include <string>

namespace dv {


enum class conf_visualizationTypes {
  AUTO, //if user not forces some specific type it will be recognized by context
  CHART,
  HEATMAP,
  SURFACE
};

enum class conf_colorscales {
  DEFAULT,
  SUNNY,
  GLAMOUR,
  THERMAL,
  GRAYSCALE
};


struct commonSettings{
    commonSettings():typeVisual(conf_visualizationTypes::AUTO), xLabel("X"), yLabel("Y"){}
    conf_visualizationTypes typeVisual; // мб это не должно быть здесь. Тип должен опредялться автоматически
    std::string xLabel;
    std::string yLabel;
};

struct chartSettings{

};

struct heatMapSettings{
    heatMapSettings():colorSc(conf_colorscales::DEFAULT){}
    conf_colorscales colorSc;
};

struct surfaceSettings{
    surfaceSettings():colorSc(conf_colorscales::DEFAULT), zLabel("Z"){}
    conf_colorscales colorSc;
    std::string zLabel;
};


class Configurator
{
public:
    static Configurator& getInstance(){
        static Configurator instance;
        return instance;
    }
    Configurator(Configurator const&)   = delete;
    void operator=(Configurator const&) = delete;

    void reset(){ //to default settings
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
    Configurator(){};

};

Configurator& config(){
    return Configurator::getInstance();
};

}
#endif // CONFIGURATOR_H
