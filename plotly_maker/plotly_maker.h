#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

//#START_GRAB_TO_INCLUDES_LIST
#include <vector>
#include <string>
#include <memory>
#include <iostream>
//#STOP_GRAB_TO_INCLUDES_LIST
#include "../array_core/configurator.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE

using std::vector;


bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                std::string& page, const dv::conf_visualizationTypes& type);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const std::string& title);

bool showHeatMapInBrowser(const std::string& values, const std::string& title);

bool showLineChartInBrowser(const vector<double>& values, const std::string& title);

bool showLineChartInBrowser(const std::string& values, const std::string& title);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const std::string& title);

bool showSurfaceInBrowser(const std::string& values, const std::string& title);
//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

