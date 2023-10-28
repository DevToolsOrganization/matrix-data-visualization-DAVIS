#ifndef PLOTLY_MAKER_PLOTLY_MAKER_H_
#define PLOTLY_MAKER_PLOTLY_MAKER_H_

#include "vector"
#include "string"
using std::vector;

namespace davis {

bool testPlottyMaker();
bool createHtmlPageWithPlotlyJS(const vector<vector<double>> &values, std::string &page);

}; // namespace davis

#endif // PLOTLY_MAKER_PLOTLY_MAKER_H_

