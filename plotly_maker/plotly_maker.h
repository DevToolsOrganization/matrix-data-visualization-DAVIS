#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

// #START_GRAB_TO_INCLUDES_LIST
#include <iostream>
#include <memory>
#include <string>
#include <vector>
// #STOP_GRAB_TO_INCLUDES_LIST
#include "../array_core/configurator.h"

namespace dvs {
// #START_GRAB_TO_DVS_NAMESPACE

using std::istringstream;
using std::string;
using std::vector;

bool createHtmlPageHeatmap(const vector<vector<double>> &values, string &page,
                           const dv::Config &configuration);

bool showHeatMapInBrowser(const vector<vector<double>> &values,
                          const string &title, const dv::Config &configuration);
bool showHeatMapInBrowser(const string &values, const string &title,
                          const dv::Config &configuration);

bool showLineChartInBrowser(const vector<double> &values, const string &title,
                            const dv::Config &configuration);
bool showLineChartInBrowser(const vector<double> &xValues,
                            const vector<double> &yValues, const string &title,
                            const dv::Config &configuration);
bool showLineChartInBrowser(const string &values, const string &title,
                            const dv::Config &configuration);

void showWarningJsAbsentPage();

void showReportPage(const string &page, const string &title, const string &svg,
                    const string &description);

void showReportFileNotFounded();

void showReportFileEmpty();

void showMatrixSizesAreNotTheSame(int badRow);

void showDateTimeChart(const string &date_time_values,
                       const vector<double> &yValues, bool isFitPlotToWindow);

void addTraceBlockToGlobal(const vector<double> &yValues,
                           const string &traceName);
void addTraceBlockToGlobal(const vector<double> &xValues,
                           const vector<double> &yValues,
                           const string &traceName);

void showCloudOfPointsChart(const vector<double> &xValues,
                            const vector<double> &yValues,
                            const vector<double> &colorValues,
                            bool isFitPlotToWindow);

void showCloudOfPointsChartStr(const string &xValues,
                               const vector<double> &yValues,
                               const vector<double> &colorValues,
                               bool isFitPlotToWindow);

void showMultiChart(const string &date_time_values,
                    const vector<vector<double>> &yValues,
                    bool isFitPlotToWindow);

// #STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_
