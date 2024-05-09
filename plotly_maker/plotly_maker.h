#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

//#START_GRAB_TO_INCLUDES_LIST
#include <vector>
#include <string>
#include <memory>
#include <iostream>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE

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
  THERMAL,
  GRAYSCALE
};

class ShowSettings {
 public:
  virtual ~ShowSettings() {}
  visualizationTypes getVisualType() const;

 protected:
  visualizationTypes visualType;
};

class ShowSettingsHeatMap : public ShowSettings {
 public:
  ShowSettingsHeatMap(colorscales color = colorscales::DEFAULT) {
    visualType = visualizationTypes::HEATMAP;
    colorScale = color;
  }
  colorscales colorScale;
};

class ShowSettingsSurface : public ShowSettings {
 public:
  ShowSettingsSurface(colorscales color = colorscales::DEFAULT) {
    visualType = visualizationTypes::SURFACE;
    colorScale = color;
  }
  colorscales colorScale;
};

class ShowSettingsChart : public ShowSettings {
 public:
  ShowSettingsChart() {
    visualType = visualizationTypes::CHART;
  }
};

std::unique_ptr<ShowSettingsHeatMap> createShowSettingsHeatMap(colorscales color = colorscales::DEFAULT);
std::unique_ptr<ShowSettingsSurface> createShowSettingsSurface(colorscales color = colorscales::DEFAULT);
std::unique_ptr<ShowSettingsChart> createShowSettingsChart();

bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                std::string& page,
                                const visualizationTypes& visualType,
                                const colorscales& colorscale);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const ShowSettingsHeatMap* settings);

bool showHeatMapInBrowser(const std::string& values, const std::string& title,
                          const ShowSettingsHeatMap* settings);

bool showLineChartInBrowser(const vector<double>& values, const std::string& title,
                            const ShowSettingsChart* settings);

bool showLineChartInBrowser(const std::string& values, const std::string& title,
                            const ShowSettingsChart* settings);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const ShowSettingsSurface* settings);

bool showSurfaceInBrowser(const std::string& values, const std::string& title,
                          const ShowSettingsSurface* settings);
//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

