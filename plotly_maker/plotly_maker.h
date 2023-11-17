#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

#include "vector"
#include "string"

namespace davis {

using std::vector;

enum class visualizationTypes {
  CHART,
  HEATMAP,
  SURFACE
};

enum class colorscales {
  DEFAULT,
  SUNNY,
  GLAMOUR,
  THERMAL
};

struct showSettings {
  showSettings():
    visualType(visualizationTypes::HEATMAP), //default params
    colorscale(colorscales::DEFAULT) { }
  visualizationTypes visualType = visualizationTypes::HEATMAP;
  colorscales colorscale = colorscales::DEFAULT;
};

bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                std::string& page,
                                const showSettings& settings);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const showSettings& settings);

bool showHeatMapInBrowser(const std::string& values, const std::string& title,
                          const showSettings& settings);

bool showLineChartInBrowser(const vector<double>& values, const std::string& title,
                            const showSettings& settings);

bool showLineChartInBrowser(const std::string& values, const std::string& title,
                            const showSettings& settings);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const showSettings& settings);

bool showSurfaceInBrowser(const std::string& values, const std::string& title,
                          const showSettings& settings);

bool getMatrixValuesFromString(const std::string& in_values,
                               vector<vector<double>>& out_values);
}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

