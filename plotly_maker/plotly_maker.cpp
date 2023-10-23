#include <iostream>
#include "plotly_maker.h"
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
namespace{

constexpr char kHeadPart[] =R"(<head>
<script src="./plotly-2.27.0.min.js" charset="utf-8"></script>
</head>
<body>
<div style="height:2044px; width:2044px;" id="gd"></div>
<script>
var data = [{
  z: [[7,90,876],[654,678,9],[600,5,349]])";

constexpr char kSecondPart[] =R"(,
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
  ],
  type: 'heatmap'
}];
Plotly.newPlot('gd', data);
</script>
</body>)";


}

namespace davis {

void testPlottyMaker(){

    std::string result = kHeadPart;
    result.append(kSecondPart);
    std::ofstream out("example.html");
    if(out.is_open()){
        out << result.c_str();
        std::cout<<"Write to file...";
        out.close();
    }else{
        std::cout<<"Unable to open file...";
    }
}
}; // namespace davis


