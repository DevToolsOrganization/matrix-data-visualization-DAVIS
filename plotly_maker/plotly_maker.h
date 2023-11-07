#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

#include "vector"
#include "string"

using std::vector;

namespace davis {

extern const char saveFolderName[];

enum class visualizationTypes{
    graph, heatmap, surface
};

enum class colorscales{
    gray, rainbow
};

struct showSettings{
    showSettings():
        visualType(visualizationTypes::heatmap), //default params
        colorscale(colorscales::rainbow) { }
    visualizationTypes visualType = visualizationTypes::heatmap;
    colorscales colorscale = colorscales::rainbow;
};

bool createHtmlPageWithPlotlyJS(const vector<vector<double>> &values,
                                std::string &page);
bool showHeatMapInBrowser(const vector<vector<double>> &values, const std::string &title, const showSettings &settings);

bool showLineChartInBrowser(const vector<double> &values, const std::string &title, const showSettings &settings);

}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

