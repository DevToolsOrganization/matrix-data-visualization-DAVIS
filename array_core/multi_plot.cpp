#include "multi_plot.h"
#include "plotly_maker/html_parts.h"
#include "plotly_maker/plotly_maker.h"
#include "common_utils/common_utils.h"
#include "common_utils/common_constants.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE

bool isHold = false;
std::vector<std::string> allChartBlocks = {};

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
  if (dvs::allChartBlocks.empty()) {
    return;
  }
  std::string allTracesNames_str;
  std::string allChartBlocks_str;
  const std::string trace_name_part = "trace";
  for (int i = 0; i < dvs::allChartBlocks.size(); ++i) {
    std::string str_numTrace = std::to_string(i + 1);
    std::string filled_trace_name_part = trace_name_part + str_numTrace;
    if (i < dvs::allChartBlocks.size() - 1) {
      filled_trace_name_part.append(",");
    }
    allTracesNames_str.append(filled_trace_name_part);
    allChartBlocks_str.append(dvs::allChartBlocks[i]);
  }
  std::string paramWH;
  if (configuration.chart.aspectRatioWidth > configuration.chart.aspectRatioHeight) {
    paramWH = "width";
  } else {
    paramWH = "height";
  }
  std::string paramWHsecond;
  if (configuration.chart.isFitPlotToWindow) {
    if (paramWH == "width") {
      paramWHsecond = "height";
    } else if (paramWH == "height") {
      paramWHsecond = "width";
    }
  } else {
    paramWHsecond = paramWH;
  }
  std::vector<std::string> args = {dvs::kPlotlyJsName,
                                   allChartBlocks_str,
                                   allTracesNames_str,
                                   configuration.chart.title,
                                   configuration.chart.xLabel,
                                   configuration.chart.yLabel,
                                   dvs::toStringDotSeparator(configuration.chart.aspectRatioWidth),
                                   dvs::toStringDotSeparator(configuration.chart.aspectRatioHeight),
                                   paramWH,
                                   paramWHsecond,
                                   dvs::kHtmlComboboxStyleBlock,
                                   dvs::kHtmlComboboxSelectBlock,
                                   dvs::kHtmlComboboxUpdateFooBlock,
                                   dvs::kHtmlDavisLogoHyperlinkBlock
                                  };
  std::string multichartPage = dvs::kHtmlMultiChartModel;
  std::string filled_multichartPage = "";
  dvs::make_string(multichartPage, args, filled_multichartPage);
  std::string htmlFullName = dvs::makeUniqueDavisHtmlRelativePath();
  dvs::mayBeCreateJsWorkingFolder();
  dvs::saveStringToFile(htmlFullName, filled_multichartPage);
  if (dvs::isPlotlyScriptExists()) {
    dvs::openPlotlyHtml(htmlFullName);
  } else {
    dvs::showWarningJsAbsentPage();
  }
  dvs::allChartBlocks.clear();
}



//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dv
