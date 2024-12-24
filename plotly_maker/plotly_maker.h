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
                                const dv::Config& configuration,
                                dv::config_visualizationTypes typeVisual);

bool showHeatMapInBrowser(const vector<vector<double>>& values, const string& title, const dv::Config& configuration);

bool showHeatMapInBrowser(const string& values, const string& title, const dv::Config& configuration);

bool showLineChartInBrowser(const vector<double>& values, const string& title, const dv::Config& configuration);
bool showLineChartInBrowser(const vector<double>& xValues, const vector<double>& yValues,
                            const string& title, const dv::Config& configuration);

bool showLineChartInBrowser(const string& values, const string& title, const dv::Config& configuration);

bool showSurfaceInBrowser(const vector<vector<double>>& values, const string& title, const dv::Config& configuration);

bool showSurfaceInBrowser(const string& values, const string& title, const dv::Config& configuration);

void showWarningJsAbsentPage();


void showReportPage(const string& page, const string& title, const string& svg, const string& description);

void showReportFileNotFounded();

void showReportFileEmpty();

void showMatrixSizesAreNotTheSame(int badRow);

void showDateTimeChart(const string& date_time_values,
                       const vector<double>& yValues,
                       bool isAutoScale);

void addTraceBlockToGlobal(const vector<double>& yValues, const string& traceName);
void addTraceBlockToGlobal(const vector<double>& xValues, const vector<double>& yValues, const string& traceName);

void showCloudOfPointsChart(const vector<double>& xValues,
                            const vector<double>& yValues,
                            const vector<double>& colorValues,
                            bool isAutoScale);


void showCloudOfPointsChartStr(const string& xValues,
                               const vector<double>& yValues,
                               const vector<double>& colorValues,
                               bool isAutoScale);

void showDateTimeMultichart(const string& date_time_values,
                            const vector<vector<double>>& yValues);

//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

