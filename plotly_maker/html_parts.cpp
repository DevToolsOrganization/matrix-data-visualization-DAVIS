#include "html_parts.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
// *INDENT-OFF*
    const char kHtmlModel[] =
R"(
<head>
<script src="./plotly-2.27.0.min.js" charset="utf-8"></script>
</head>
<body><div style = "display: flex;
  align-items:center;height:100%; width:100%;background:#dddfd4;
  justify-content: center;"><div style="height:95%; aspect-ratio: 1/1;"
id="gd"></div></div>
<script>
%1
%2
%3
var layout = {
  title: {
    text:'%4'
  },
  xaxis: {
    title: {
      text: '%5'
    },
  },
  yaxis: {
    title: {
      text: '%6'
    }
  }
};
var config = {
  editable: true,
  showLink: true,
  plotlyServerURL: "https://chart-studio.plotly.com"
};
Plotly.newPlot('gd', data, layout, config);
</script>
</body>
)";

    const char kColorMapDefaultPart[] = R"(
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


    const char kColorMapSunnyPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(250, 134, 7)'],
    ['0.2', 'rgb(250, 150, 27)'],
    ['0.4', 'rgb(252, 176, 51)'],
    ['0.6', 'rgb(254, 204, 81)'],
    ['0.8', 'rgb(255, 228, 105)'],
    ['1.0', 'rgb(255, 245, 123)']
  ],)";

    const char kColorMapGlamourPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(17,63,93)'],
    ['0.2', 'rgb(88,80,143)'],
    ['0.4', 'rgb(182,79,145)'],
    ['0.6', 'rgb(245,97,94)'],
    ['0.8', 'rgb(248,165,0)'],
    ['1.0', 'rgb(235,248,0)']
  ],)";

    const char kColorMapThermalPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(0,0,5)'],
    ['0.2', 'rgb(12,0,44)'],
    ['0.4', 'rgb(41,0,148)'],
    ['0.6', 'rgb(196,0,123)'],
    ['0.8', 'rgb(230,61,63)'],
    ['1.0', 'rgb(255,213,0)']
  ],)";


    const char kColorMapGrayscalePart[] = R"(
  colorscale: [
    ['0.0', 'rgb(0,0,0)'],
    ['1.0', 'rgb(255, 255, 255)']
  ],)";

    const char kHeatMapTypePart[] = R"(
type: 'heatmap',
hovertemplate: 'x:%{x} <br>y:%{y} <br>val:%{z:.}<extra></extra>',
colorbar: {
  title: ""
}
}];)";

    const char kSurfaceTypePart[]=R"(
type: 'surface',
hovertemplate: 'x:%{x} <br>y:%{y} <br>z:%{z:.}<extra></extra>',
colorbar: {
  title: ""
}
}];)";
// *INDENT-ON*
//#STOP_GRAB_TO_DVS_NAMESPACE
} // namespace dvs
