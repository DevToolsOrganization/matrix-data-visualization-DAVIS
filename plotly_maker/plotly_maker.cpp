#include <io.h>
#include <iostream>
#include "plotly_maker.h"
#include "common_utils/common_utils.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "html_parts.h"

namespace{

constexpr char kDivSizePart[] =R"(<div style="height:1022px; width:1022px;"
id="gd"></div>
<script>
)";


bool checkThatSizesAreTheSame(const std::vector<std::vector<double>> &values) {
    unsigned int size = 0;
    if(!values.empty()) {
        size = values[0].size();
    };
    for(unsigned int i=0;i<values.size();++i){

      if(values[i].size() != size)return false;
    }
    return true;
}

bool createStringHeatMapValues(const std::vector<std::vector<double>> &values,
                        std::string &str_values){
    if(!checkThatSizesAreTheSame(values))return false;
    if(!str_values.empty())str_values.clear();
    str_values.append(R"(var data = [{z: )");
    str_values.append(R"([)");
    for(unsigned int i=0;i<values.size();++i){
        str_values.append("[");
        for(unsigned int j=0;j<values[i].size();++j){
            str_values.append(std::to_string(values[i][j]));
            if(j!=values[i].size()-1)str_values.append(",");
        }
        str_values.append("]");
        if(i!=values.size()-1)str_values.append(",");
    }
    str_values.append(R"(],)");
    return true;
}

bool createStringLineChartValues(const std::vector<double> &values,
                                 std::string &str_values){
    if(!str_values.empty())str_values.clear();
    str_values = R"(var trace = {
x: [)";
    for(int i=0;i<values.size();++i){
        str_values.append(std::to_string(i));
        if(i!=values.size()-1)str_values.append(",");
    }
    str_values.append("], y: [");
    for(int j=0;j<values.size();++j){
    str_values.append(std::to_string(values[j]));
    if(j!=values.size()-1)str_values.append(",");
    }
    str_values.append("], mode: 'lines+markers'};var data = [trace];");
    return true;
}

} // namespace

namespace davis {

bool createHtmlPageWithPlotlyJS(const std::vector<std::vector<double>> &values,
                                std::string &page)
{
    page = kCommonHeadPart;
    page.append(kDivSizePart);
    std::string str_values = "";
    if(!checkThatSizesAreTheSame(values))return false;
    createStringHeatMapValues(values, str_values);
    page.append(str_values);
    page.append(kColorMapDefaultPart);
    page.append(kCommonLastPart);
    return true;
}

bool showDataInBrowser(const vector<vector<double>> &values){
    std::string page;
    if(!createHtmlPageWithPlotlyJS(values,page))return false;
    davis::saveStringToFile("example.html",page);
    openPlotlyHtml();
    return true;

}


bool showDataInBrowser(const vector<double> &values){
    // Заглушка
    // Valery, you need to create overload createHtmlPageWithPlotlyJS with
    // input argument const vector<double> &values
    // In this case it will be possible to plot graphics for 1 vector instead of heatmap

    vector<vector<double>> wrapper;
    wrapper.push_back(values);
    return showDataInBrowser(wrapper);
}

bool showLineChartInBrowser(const vector<double> &values){
    std::string page = kCommonHeadPart;
    page.append(kDivSizePart);
    std::string str_values = "";
    createStringLineChartValues(values,str_values);
    page.append(str_values);
    page.append(kCommonLastPart);
    davis::saveStringToFile("example.html",page);
    openPlotlyHtml();
    return true;
}

}; // namespace davis


