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

using std::string;
using std::vector;
using std::istringstream;


bool createHtmlPageWithPlotlyJS(const vector<vector<double>>& values,
                                string& page,
                                const dv::config_visualizationTypes& type);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const string& title);

bool showHeatMapInBrowser(const string& values, const string& title);

bool showLineChartInBrowser(const vector<double>& values, const string& title);

bool showLineChartInBrowser(const string& values, const string& title);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const string& title);

bool showSurfaceInBrowser(const string& values, const string& title);
//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

