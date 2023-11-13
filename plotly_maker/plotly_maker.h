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

//struct showSettings {
//    showSettings():
//        visualType(visualizationTypes::HEATMAP),
//        colorscale(colorscales::THERMAL) { }
//    visualizationTypes visualType = visualizationTypes::HEATMAP;
//    colorscales colorscale = colorscales::THERMAL;
//};


class showSettings{
public:
    virtual ~showSettings() {}
    visualizationTypes visualType;
};

class showSettingsHeatMap : public showSettings{
public:
    showSettingsHeatMap()
    {
        visualType = visualizationTypes::HEATMAP;
        colorSc = colorscales::DEFAULT;
    }
    colorscales colorSc;
};

class showSettingsSurface : public showSettings{
public:
    showSettingsSurface()
    {
        visualType = visualizationTypes::SURFACE;
        colorSc = colorscales::DEFAULT;
    }
    colorscales colorSc;
};

class showSettingsChart : public showSettings{
public:
    showSettingsChart(){
        visualType = visualizationTypes::CHART;
    }
};

bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                std::string& page,
                                const visualizationTypes& visualType,
                                const colorscales& colorscale);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const showSettingsHeatMap& settings);

bool showHeatMapInBrowser(const std::string& values, const std::string& title,
                          const showSettingsHeatMap& settings);

bool showLineChartInBrowser(const vector<double>& values, const std::string& title,
                            const showSettingsChart& settings);

bool showLineChartInBrowser(const std::string& values, const std::string& title,
                            const showSettingsChart& settings);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const std::string& title,
                          const showSettingsSurface &settings);
}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

