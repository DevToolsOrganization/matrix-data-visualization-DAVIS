#include <io.h>
#include <iostream>
#include "plotly_maker.h"

#include <vector>
#include <iostream>
#include <fstream>

namespace{

inline bool is_file_exists (const std::string &file) {
    return ( access( file.c_str(), F_OK ) != -1 );
}


constexpr char kHeadPart[] =R"(<head>
<script src="./plotly-2.27.0.min.js" charset="utf-8"></script>
</head>
<body>
<div style="height:2044px; width:2044px;" id="gd"></div>
<script>)";

constexpr char kColorMap1Part[] =R"(
  colorscale: [
    ['0.0', 'rgb(165,0,38)'],
    ['0.111111111111', 'rgb(215,48,39)'],
    ['0.222222222222', 'rgb(244,109,67)'],
    ['0.333333333333', 'rgb(253,174,97)'],
    ['0.444444444444', 'rgb(254,224,144)'],
    ['0.555555555556', 'rgb(224,243,248)'],
    ['0.666666666667', 'rgb(171,217,233)'],
    ['0.777777777778', 'rgb(116,173,209)'],
    ['0.888888888889', 'rgb(69,117,180)'],
    ['1.0', 'rgb(49,54,149)']
  ],)";

constexpr char kLastPart[] =R"(  
  type: 'heatmap'
}];
Plotly.newPlot('gd', data);
</script>
</body>)";

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

bool createStringValues(const std::vector<std::vector<double>> &values,
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

} // namespace

namespace davis {

//TODO this test will be moved to tests
bool testPlottyMaker(){

    std::string result = kHeadPart;
    std::string str_values = "";
    std::vector<std::vector<double>>testValues = {{43,400,54,980},{200,36,400,55},{120,4,650,5}};
    if(!checkThatSizesAreTheSame(testValues))return false;
    createStringValues(testValues,str_values);
    result.append(str_values);
    std::cout<<result;
    result.append(kColorMap1Part);
    result.append(kLastPart);
    std::ofstream out("example.html");
    if(out.is_open()){
        out << result.c_str();
        std::cout<<"Write to file...";
        out.close();
    }else{
        std::cout<<"Unable to open file...";
    }
  return true;
}
}; // namespace davis


