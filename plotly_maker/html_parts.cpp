#include "html_parts.h"

namespace davis {

const char kCommonHeadPart[] = R"(<head>
<script src="./plotly-2.27.0.min.js" charset="utf-8"></script>
</head>
<body>)";

const char kCommonLastPart[] = R"(
Plotly.newPlot('gd', data);
</script>
</body>)";

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
  ],
type: 'heatmap'
}];)";

} // namespace davis
