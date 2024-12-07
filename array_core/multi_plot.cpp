#include "multi_plot.h"
#include "plotly_maker/html_parts.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE

bool isHold = false;
vector<string> allChartBlocks = {};

//#STOP_GRAB_TO_DVS_NAMESPACE
} // end namespace dvs


namespace dv {
//#START_GRAB_TO_DV_NAMESPACE

void holdOn() {
  dvs::isHold = true;
  dvs::allChartBlocks.clear();

}

void holdOff(const Config& configuration) {
  dvs::isHold = false;
  string allTracesNames_str;
  string allChartBlocks_str;
  const string trace_name_part = "trace";
  for (int i = 0; i < dvs::allChartBlocks.size(); ++i) {
    string str_numTrace = std::to_string(i + 1);
    string filled_trace_name_part = trace_name_part + str_numTrace;
    if (i < dvs::allChartBlocks.size() - 1) {
      filled_trace_name_part.append(",");
    }
    allTracesNames_str.append(filled_trace_name_part);
    allChartBlocks_str.append(dvs::allChartBlocks[i]);
  }
  vector<string> args = {dvs::kPlotlyJsName, allChartBlocks_str, allTracesNames_str,
                         configuration.chart.title, configuration.chart.xLabel, configuration.chart.yLabel
                        };
  string multichartPage = dvs::kHtmlMultiChartModel;
  string filled_multichartPage = "";
  dvs::make_string(multichartPage, args, filled_multichartPage);
  string htmlFullName = dvs::makeUniqueDavisHtmlName();
  dvs::saveStringToFile(htmlFullName, filled_multichartPage);
  dvs::openFileBySystem(htmlFullName);
  dvs::allChartBlocks.clear();
}



//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dv
