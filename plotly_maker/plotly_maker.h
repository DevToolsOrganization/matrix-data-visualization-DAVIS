#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

#include "vector"
#include "string"

using std::vector;

namespace davis {

bool createHtmlPageWithPlotlyJS(const vector<vector<double>> &values,
                                std::string &page);
bool showHeatMapInBrowser(const vector<vector<double>> &values);
bool showHeatMapInBrowser(const std::string &values);

bool showLineChartInBrowser(const vector<double> &values);
bool showLineChartInBrowser(const std::string &values);
}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

