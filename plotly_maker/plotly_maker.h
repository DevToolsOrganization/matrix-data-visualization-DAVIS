#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

#include "vector"
#include "string"
using std::vector;

namespace davis {

bool createHtmlPageWithPlotlyJS(const vector<vector<double>> &values,
                                std::string &page);
bool showDataInBrowser(const vector<vector<double>> &values);
bool showDataInBrowser(const vector<double> &values);

}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

