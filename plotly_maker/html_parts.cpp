#include "html_parts.h"

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
// *INDENT-OFF*
    const char kHtmlModel[] =
R"(
<head>
  <script src="./%8" charset="utf-8"></script>
  %13
</head>
<body>
  <div style="display: flex; align-items: center; height: 100%; width: 100%; background: #dddfd4; justify-content: center;">
    <div style="%11: 99%; %12: 99%; aspect-ratio: %9/%10;" id="gd"></div>
  </div>
  %16
  %14
  <script>
    %1
    %2
    %3
    var layout = {
      title: {
        text: '%4'
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
      },
      scene: {
        xaxis: {
          title: '%5',
        },
        yaxis: {
          title: '%6',
        },
        zaxis: {
          title: '%7',
        }
      }
    };
    var config = {
      editable: true,
      showLink: true,
      plotlyServerURL: "https://chart-studio.plotly.com"
    };
    Plotly.newPlot('gd', data, layout, config);
    %15
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

    const char kColorMapYlGnBuPart[] = R"(
  colorscale: 'YlGnBu',
  )";

    const char kColorMapJetPart[] = R"(
  colorscale: 'Jet',
  )";

    const char kColorMapHotPart[] = R"(
  colorscale: 'Hot',
  )";

    const char kColorMapElectricPart[] = R"(
  colorscale: 'Electric',
  )";

    const char kColorMapPortlandPart[] = R"(
  colorscale: 'Portland',
  )";

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

const char kWarningJSLibAbsentPage[] = R"(
<html>
<head>
<style>
.coffe_img {
margin:2%;
display: grid;
grid-template-columns: 33% 66%
}
.dont_worry{
padding-top:5%
}
.download{

}
.download_text{
margin-left:2%;
margin-top:5%;
color:#34495E;
font-size: 40px;
font-family:calibri
}
.worry_text{
color:#3498DB;
font-size: 40px;
font-family:calibri
}

.link_style{
padding-top:2%;
padding-left:2%;
color:#34495E;
font-size: 40px;
font-family:calibri
}

.email_style{
padding-top:6%;
padding-left:35%;
color:#34495E;
font-size: 40px;
font-family:calibri
}

</style>
</head>
<div class="coffe_img">
<div>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<!-- Creator: CorelDRAW 2020 (64-Bit) -->
<svg xmlns="http://www.w3.org/2000/svg" xml:space="preserve" width="112.371mm" height="82.3636mm" version="1.1" style="shape-rendering:geometricPrecision; text-rendering:geometricPrecision; image-rendering:optimizeQuality; fill-rule:evenodd; clip-rule:evenodd"
viewBox="0 0 11237.16 8236.39"
 xmlns:xlink="http://www.w3.org/1999/xlink"
 xmlns:xodm="http://www.corel.com/coreldraw/odm/2003">
 <defs>
  <style type="text/css">
   <![CDATA[
    .fil8 {fill:#878787;fill-rule:nonzero}
    .fil0 {fill:#9D9D9C;fill-rule:nonzero}
    .fil7 {fill:#BC926F;fill-rule:nonzero}
    .fil6 {fill:#C69A71;fill-rule:nonzero}
    .fil5 {fill:#CEA275;fill-rule:nonzero}
    .fil4 {fill:#E0B1B1;fill-rule:nonzero}
    .fil10 {fill:#E0C0A6;fill-rule:nonzero}
    .fil11 {fill:#EDEDED;fill-rule:nonzero}
    .fil2 {fill:#EFBDBB;fill-rule:nonzero}
    .fil3 {fill:#F7D0CD;fill-rule:nonzero}
    .fil1 {fill:#F9C7C3;fill-rule:nonzero}
    .fil9 {fill:white;fill-rule:nonzero;fill-opacity:0.678431}
   ]]>
  </style>
 </defs>
 <g id="Слой_x0020_1">
  <metadata id="CorelCorpID_0Corel-Layer"/>
  <g id="_2622218307280">
   <ellipse class="fil0" cx="7672.67" cy="8004.42" rx="441.5" ry="102.27"/>
   <ellipse class="fil0" cx="9141.85" cy="7605.33" rx="441.5" ry="102.27"/>
   <ellipse class="fil0" cx="10825.55" cy="6914.38" rx="339.23" ry="77.32"/>
   <ellipse class="fil0" cx="3260.13" cy="7682.65" rx="3260.13" ry="553.74"/>
   <path class="fil1" d="M6662.45 3332.47l0 4215.48c0,319.28 -853.07,581.19 -1905.7,581.19 -1052.62,0 -1905.7,-259.41 -1905.7,-581.19l0 -4215.48 0 0c7.48,319.28 858.06,576.2 1905.7,576.2 1047.63,2.49 1898.22,-256.92 1905.7,-576.2l0 0z"/>
   <path class="fil2" d="M4729.32 8129.14c-1040.15,-4.99 -1878.26,-261.91 -1878.26,-581.19l0 -4215.48 0 0c4.99,279.37 665.99,513.84 1539.03,566.22l339.23 4230.45z"/>
   <path class="fil3" d="M6662.45 3329.98c0,2.49 0,2.49 0,4.99 -7.48,319.28 -858.06,576.2 -1905.7,576.2 -1047.63,0 -1898.22,-256.92 -1905.7,-576.2 0,-2.49 0,-2.49 0,-4.99 0,-319.28 853.07,-581.19 1905.7,-581.19 1052.62,0 1905.7,259.41 1905.7,581.19z"/>
   <path class="fil4" d="M6343.17 3327.48c0,64.85 -57.37,124.72 -157.14,179.59 -236.96,-149.66 -803.18,-254.42 -1464.2,-254.42 -628.58,0 -1169.85,94.79 -1426.78,231.98 -77.33,-47.39 -119.73,-102.27 -119.73,-157.14 0,-226.99 708.4,-414.06 1583.93,-414.06 873.02,2.48 1583.92,187.06 1583.92,414.05z"/>
   <path class="fil5" d="M6183.53 3507.08c-256.92,137.19 -798.19,231.98 -1426.78,231.98 -661,0 -1227.22,-104.76 -1464.2,-254.42 119.73,-152.16 269.39,-117.23 463.95,-192.07 316.78,-122.22 878.01,-107.26 1112.48,-67.35 251.93,44.9 503.86,-7.48 703.41,57.37 386.63,127.21 566.22,84.8 611.12,224.49z"/>
   <path class="fil6" d="M5934.1 3604.36c-289.35,82.31 -708.4,134.7 -1174.84,134.7 -471.43,0 -895.47,-54.88 -1184.82,-139.68 119.73,-44.9 241.95,-87.3 364.18,-127.21 64.85,-19.95 129.71,-39.91 197.05,-44.9 109.75,-9.98 222,19.95 331.75,32.43 259.41,32.43 526.31,-17.46 783.23,29.93 59.86,12.47 119.73,27.44 179.59,34.92 69.84,7.48 137.19,4.99 207.03,9.98 99.77,9.96 202.04,32.41 296.83,69.83z"/>
   <path class="fil1" d="M8685.38 5278.08c0,830.62 -673.48,1501.61 -1501.61,1501.61 -182.09,0 -359.19,-32.43 -521.32,-92.29l0 -770.76c142.18,114.74 321.77,184.58 521.32,184.58 453.97,0 823.14,-369.16 823.14,-823.14 0,-453.97 -369.16,-823.14 -823.14,-823.14 -197.05,0 -379.14,69.84 -521.32,184.58l0 -770.76c162.13,-59.86 336.74,-92.29 521.32,-92.29 828.13,0.02 1501.61,673.49 1501.61,1501.63z"/>
   <path class="fil2" d="M7141.38 3776.47l0 678.47c-182.09,9.98 -346.72,77.33 -478.92,184.58l0 -770.76c149.66,-54.88 311.79,-87.31 478.92,-92.29z"/>
   <path class="fil2" d="M6662.45 5916.64c132.2,107.26 296.83,174.61 478.92,184.58l0 678.47c-167.12,-4.99 -329.26,-37.42 -478.92,-92.29l0 -770.76z"/>
   <path class="fil6" d="M7952.04 7370.86c-341.73,-107.26 -334.24,137.19 -311.79,174.61 -119.73,74.83 22.45,374.15 112.25,446.49 239.46,192.07 448.98,9.98 486.4,-139.68 47.39,-187.09 -127.22,-434.03 -286.86,-481.42zm92.29 518.82c-7.48,-22.45 -17.46,-44.9 -29.93,-64.85 -9.98,-19.95 -24.94,-39.91 -39.91,-54.88 -27.44,-34.92 -64.85,-57.37 -107.26,-69.84 -9.98,-4.99 -19.95,-4.99 -32.43,-7.48 -9.98,-2.49 -22.45,-2.49 -34.92,-4.99 -24.94,-4.99 -49.89,-9.98 -72.34,-19.95 -24.94,-9.98 -47.39,-27.44 -62.36,-47.39 -14.97,-19.95 -22.45,-47.39 -22.45,-72.34 9.98,22.45 22.45,42.4 39.91,54.88 17.46,14.97 37.42,22.45 57.37,27.44 19.95,4.99 42.4,7.48 67.35,9.98 22.45,2.49 49.89,4.99 74.83,12.47 49.89,14.97 97.28,49.89 122.22,94.79 14.97,22.45 24.94,44.9 29.93,69.84 7.5,22.44 12.49,47.38 9.99,72.32z"/>
   <path class="fil7" d="M7605.33 7590.36c-42.4,112.25 72.34,339.23 149.66,401.59 189.57,152.16 361.68,67.35 444,-47.39 -336.75,49.89 -508.86,-167.12 -593.66,-354.2z"/>
   <path class="fil6" d="M9710.56 7450.68c-157.14,366.67 -521.32,197.05 -628.58,99.77 -241.95,-217.01 -89.8,-291.84 -52.38,-304.31 12.47,9.98 27.44,19.95 42.4,27.44 22.45,12.47 47.39,24.94 72.34,34.92 47.39,19.95 97.28,34.92 149.66,47.39 49.89,12.47 102.27,24.94 152.16,32.43 52.38,7.48 102.27,12.47 154.65,12.47 -47.39,-19.95 -97.28,-34.92 -147.17,-49.89 -49.89,-14.97 -99.77,-27.44 -149.66,-42.4 -49.89,-12.47 -99.77,-24.94 -149.66,-37.42 -24.94,-7.48 -49.89,-12.47 -74.83,-19.95 -14.97,-4.99 -32.43,-9.98 -47.39,-14.97 -19.95,-37.42 -107.26,-234.47 231.98,-226.99 396.6,12.48 481.4,364.18 446.48,441.51z"/>
   <path class="fil7" d="M9633.24 7577.89c-177.1,194.56 -456.47,57.37 -548.76,-24.94 -197.05,-177.1 -132.2,-259.41 -82.31,-291.84 74.83,139.68 244.44,289.34 631.07,316.78z"/>
   <path class="fil6" d="M11237.12 6764.72c-14.97,249.44 -264.4,226.99 -346.72,192.07 -187.08,-74.83 -114.74,-152.16 -94.79,-167.12 9.98,2.49 19.95,4.99 32.43,7.48 17.46,2.49 32.43,4.99 49.89,4.99 32.43,0 64.85,0 97.28,-2.49 32.43,-2.49 64.85,-7.48 97.28,-14.97 32.43,-7.48 62.36,-14.97 94.79,-24.94 -32.43,-2.49 -64.85,0 -97.28,2.49 -32.43,2.49 -64.85,4.99 -94.79,7.48 -32.43,2.49 -64.85,7.48 -94.79,9.98 -14.97,2.49 -32.43,2.49 -47.39,4.99 -9.98,0 -19.95,2.49 -29.93,2.49 -19.95,-17.46 -112.25,-114.74 87.3,-182.09 224.5,-82.32 349.22,107.26 346.72,159.64z"/>
   <path class="fil7" d="M11217.17 6854.51c-62.36,152.16 -256.92,132.2 -326.76,102.27 -152.16,-62.36 -134.7,-122.22 -109.75,-152.16 72.33,67.35 204.53,117.24 436.51,49.89z"/>
   <circle class="fil8" cx="3856.29" cy="5303.02" r="84.81"/>
   <circle class="fil8" cx="4806.65" cy="5303.02" r="84.81"/>
   <path class="fil8" d="M4499.84 5572.41c22.45,49.89 12.47,117.23 -27.44,167.12 -37.42,49.89 -102.27,82.31 -167.12,79.82 -64.85,0 -129.71,-29.93 -167.12,-79.82 -37.42,-49.89 -49.89,-114.74 -27.44,-167.12 22.45,49.89 52.38,84.81 87.3,107.26 34.92,22.45 69.84,32.43 107.26,32.43 37.42,0 72.34,-9.98 107.26,-32.43 34.92,-24.94 64.85,-57.37 87.3,-107.26z"/>
   <path class="fil9" d="M7784.92 4098.24c-42.4,-12.47 24.94,-79.82 64.85,-82.31 67.35,-2.49 209.53,94.79 239.46,149.66 29.93,54.88 -87.3,69.84 -87.3,69.84 0,0 -102.27,-124.72 -217.01,-137.19z"/>
   <path class="fil11" d="M4457.44 92.29c-77.33,74.83 -149.66,152.16 -209.53,234.47 -59.86,82.31 -109.75,169.62 -134.7,259.41 -7.48,22.45 -9.98,44.9 -14.97,67.35 0,9.98 -2.49,22.45 -2.49,32.43l0 32.43c2.49,42.4 9.98,84.81 24.94,127.21 32.43,82.31 87.3,157.14 157.14,224.49l54.88 52.38 32.43 29.93c9.98,9.98 19.95,22.45 29.93,32.43 19.95,22.45 37.42,47.39 54.88,72.34 14.97,27.44 32.43,54.88 42.4,84.81 22.45,57.37 37.42,122.22 37.42,184.58 0,62.36 -12.47,122.22 -29.93,179.59 -39.91,112.25 -104.76,207.03 -177.1,286.85 -37.42,39.91 -77.33,77.33 -119.73,112.25 -42.4,34.92 -87.3,64.85 -132.2,92.29 67.35,-82.31 129.71,-169.62 182.09,-256.92 52.38,-87.3 92.29,-182.09 112.25,-271.89 9.98,-44.9 12.47,-92.29 7.48,-134.7 -4.99,-42.4 -14.97,-84.81 -34.92,-122.22l-7.48 -14.97c-2.49,-4.99 -4.99,-9.98 -7.48,-14.97l-17.46 -27.44c-14.97,-17.46 -24.94,-34.92 -42.4,-52.38 -7.48,-7.48 -14.97,-17.46 -22.45,-24.94l-24.94 -22.45 -62.36 -54.88c-19.95,-19.95 -39.91,-42.4 -59.86,-62.36 -9.98,-9.98 -17.46,-22.45 -27.44,-34.92 -9.98,-12.47 -17.46,-22.45 -27.44,-34.92 -14.97,-24.94 -32.43,-49.89 -44.9,-77.33 -7.48,-14.97 -14.97,-27.44 -19.95,-42.4 -4.99,-14.97 -9.98,-29.93 -14.97,-44.9 -17.46,-59.86 -27.44,-122.22 -22.45,-184.58 2.49,-62.36 19.95,-122.22 42.4,-177.1 47.39,-109.75 119.73,-199.55 202.04,-271.89 42.4,-37.42 84.81,-69.84 132.2,-99.77 47.39,-29.92 94.78,-54.86 144.67,-77.31z"/>
   <path class="fil11" d="M5430.24 0c-84.81,94.79 -159.64,194.56 -219.5,301.82 -59.86,104.76 -107.26,217.01 -129.71,331.75 -9.98,57.37 -14.97,112.25 -12.47,169.62 2.49,54.88 12.47,109.75 27.44,164.63 32.43,107.26 89.8,207.03 164.63,294.33l59.86 69.84c9.98,12.47 22.45,27.44 32.43,39.91l29.93 42.4c9.98,14.97 17.46,29.93 27.44,44.9 7.48,14.97 17.46,29.93 24.94,47.39 7.48,17.46 14.97,32.43 22.45,49.89 4.99,17.46 12.47,34.92 17.46,49.89 39.91,137.19 37.42,284.36 0,414.06 -34.92,132.2 -94.79,249.44 -169.62,356.69 -37.42,52.38 -77.33,104.76 -122.22,149.66 -22.45,22.45 -44.9,47.39 -67.35,67.35 -24.94,22.45 -47.39,42.4 -72.34,62.36 72.34,-104.76 134.7,-214.51 184.58,-324.27 52.38,-112.25 89.8,-226.99 107.26,-341.73 7.48,-57.37 12.47,-114.74 7.48,-169.62 -4.99,-54.88 -14.97,-109.75 -32.43,-162.13 -17.46,-52.38 -44.9,-99.77 -74.83,-144.67l-24.94 -34.92c-9.98,-9.98 -17.46,-22.45 -27.44,-32.43l-62.36 -72.34c-12.47,-12.47 -19.95,-27.44 -29.93,-39.91l-29.93 -42.4c-9.98,-14.97 -17.46,-29.93 -27.44,-42.4 -7.48,-14.97 -19.95,-29.93 -24.94,-44.9 -14.97,-32.43 -32.43,-62.36 -42.4,-94.79 -4.99,-17.46 -12.47,-32.43 -17.46,-49.89l-14.97 -49.89c-14.97,-67.35 -24.94,-139.68 -22.45,-209.53 2.49,-69.84 14.97,-139.68 34.92,-204.54 39.91,-132.2 109.75,-246.94 194.56,-346.72 42.4,-49.89 87.3,-97.28 137.19,-137.19 44.9,-39.89 94.79,-79.8 152.16,-112.22z"/>
  </g>
 </g>
</svg>
</div>
<div class ="dont_worry">
<p class="worry_text">If you see this page it means that %2
<br>file is absent...</br>
</p>
<div class="worry_text">But don't worry!</div>
</div>
</div>

<div class="download_text">
Please download this .js file and add to the directory
<div class="worry_text">
%1
</div>
</div>
<div class ="link_style">

Download plotly javascript library from
<a href="https://github.com/DevToolsOrganization/matrix-data-visualization-DAVIS">our github</a>
or
<a href="https://cdn.plot.ly/plotly-2.32.0.min.js">official plotly site</a>


<div class="email_style">
For any questions please contact
<br>devtools.public@gmail.com</br>
<div>
</div>
</div>
</html>
)";



const char kNoFileFoundedPage[] = R"(<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>%1</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f8f9fa;
            color: #333;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        .container {
            text-align: center;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 10px;
            background-color: #fff;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }
        h1 {
            font-size: 2em;
            margin-bottom: 10px;
        }
        p {
            font-size: 1.2em;
        }
    </style>
</head>
<body>
    <div class="container">
    <p>%1</p>
    <?xml version="1.0" encoding="UTF-8" standalone="no"?>
        <h1>%2</h1>
        <p>%3</p>
    </div>
</body>
</html>


)";


const char kWarningIcon[] = R"davis_delimeter(<svg xmlns="http://www.w3.org/2000/svg" width="50%" height="50%" viewBox="0 0 156.262 144.407"><path d="M-109.166 7.227a2 2 0 0 0-.406.046c-3.195.03-6.176 1.695-7.785 4.483l-31.25 54.127-31.25 54.127h.002c-3.42 5.922 1.017 13.609 7.855 13.61h125.002c6.839-.001 11.277-7.688 7.857-13.61l-31.25-54.127-31.252-54.127c-1.465-2.539-4.079-4.164-6.978-4.45a2 2 0 0 0-.445-.077h-.004a2.006 2.006 0 0 0-.094-.002z" color="#000" style="solid-color:#000" transform="translate(186.615 2.437) scale(.99073)"/><path fill="#fff" d="M-109.165 9.227a7.081 7.081 0 0 0-6.46 3.529l-31.25 54.127-31.25 54.127c-2.674 4.631.777 10.609 6.126 10.61h125.002c5.348-.001 8.8-5.979 6.125-10.61l-31.25-54.127-31.252-54.127a7.079 7.079 0 0 0-5.79-3.53h-.001z" color="#000" style="solid-color:#000" transform="translate(186.615 2.437) scale(.99073)"/><path d="M-109.26 11.225a5.073 5.073 0 0 0-4.632 2.53l-31.25 54.128-31.25 54.127c-1.953 3.381.488 7.609 4.393 7.61h125.002c3.905-.001 6.345-4.229 4.392-7.61l-31.25-54.127-31.252-54.127a5.073 5.073 0 0 0-4.152-2.531z" color="#000" style="solid-color:#000" transform="translate(186.615 2.437) scale(.99073)"/><path fill="#fc0" d="M140.053 125.83H16.209L47.17 72.204l30.961-53.626 30.961 53.626z"/><g transform="translate(.295 2.437) scale(.99073)"><circle cx="78.564" cy="111.117" r="8.817"/><path d="M78.564 42.955a8.817 8.817 0 0 0-8.818 8.816l3.156 37.461a5.662 5.662 0 0 0 11.325 0l3.154-37.46a8.817 8.817 0 0 0-8.817-8.817z"/></g></svg>)davis_delimeter";



const char kHtmlDateTimeModel[] = R"davis_delimeter(
<head>
<script src="%1" charset="utf-8"></script>
%7
%11
</head>
<body>
%8

<div style = "display: flex;
  align-items:center;height:100%; width:100%;background:#dddfd4;
  justify-content: center;"><div style="%5:99%; %6:99%; aspect-ratio: %3/%4;"
id="gd"></div></div>

%10
%12
<script>
var temp = [];
var average = [
%14
];
var data = [
%2
];
%9
var config = {
  editable: true,
  showLink: true,
  plotlyServerURL: "https://chart-studio.plotly.com"
};

Plotly.newPlot('gd', data);
%13
</script>
</body>
)davis_delimeter";



const char kHtmlMultiChartBlock[] = R"davis_delimeter(
var trace%1 = {
  x: [%2],
  y: [%3],
  mode: 'lines',
  name: '%4'
};
)davis_delimeter";




const char kHtmlMultiChartModel[] = R"davis_delimeter(
<head>
<script src="%1" charset="utf-8"></script>
%11
</head>
<body>
%14
%12
<div style = "display: flex;
  align-items:center;height:100%; width:100%;background:#dddfd4;
  justify-content: center;"><div style="%9:99%; %10:99%; aspect-ratio: %7/%8;"
id="gd"></div></div>

<script>

%2

var data = [%3];
%13
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
  },
  scene: {
    xaxis: {
      title: '%5',
    },
    yaxis: {
      title: '%6',
    },
    zaxis: {
      title: '',
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
)davis_delimeter";



const char kHtmlCloudOfPoints[] = R"davis_delimeter(

<head>
<script src="%1" charset="utf-8"></script>
</head>
<body><div style = "display: flex;
  align-items:center;height:100%; width:100%;background:#dddfd4;
  justify-content: center;"><div style="%7:99%; %8:99%; aspect-ratio: %5/%6;"
id="gd"></div></div>
%9
<script>
var trace = {
x:[%2],
y:[%3],
mode: 'markers',

  marker: {
    size: 10,
    color:[%4],
    colorbar:{},
    colorscale: ''
  }
};
var data = [trace];

var config = {
  editable: true,
  showLink: true,
  plotlyServerURL: "https://chart-studio.plotly.com"
};

var layout = {};

Plotly.newPlot('gd', data,layout,config);
</script>
</body>

)davis_delimeter";

const char kHtmlSimpleDataBlock[]= R"davis_delimeter({
    x: [%1],
    y: [%2],
    mode: 'lines'
  })davis_delimeter";


const char kHtmlComboboxStyleBlock[] = R"davis_delimeter(
<style>
        #dropdown {
            position: fixed;
            top: 70px;
            left: 20px;
            z-index: 1000;
            width: 50px;
            height: 30px;
            background: no-repeat center;
            background-size: contain;
            appearance: none;
            -webkit-appearance: none;
            -moz-appearance: none;
            border: 1px solid #ccc;
            border-radius: 4px;
            padding: 5px;
            font-size: 16px;
            color:transparent;
        }

        #dropdown option {
            background: white;
            color: black;
        }
    </style>
)davis_delimeter";

const char kHtmlComboboxSelectBlock[] =R"davis_delimeter(
    <select id="dropdown" onchange="updateBackground(this)">
        <option value="image1" data-image="<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 171.373 11.261'><path d='M0 0h171.373v11.261H0z'/></svg>">line</option>
        <option value="image2" data-image="<svg width='100' height='100' xmlns='http://www.w3.org/2000/svg' viewBox='0 0 171.373 50'><g transform='translate(-20.762 -48.999)'><path d='M20.762 68.268h171.373v11.261H20.762z'/><circle cx='107.49' cy='73.999' r='25'/></g></svg>">line + point</option>
        <option value="3.svg" data-image="<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 171.373 50'><circle cx='107.49' cy='73.999' r='25' transform='translate(-20.762 -48.999)'/></svg>">point</option>
    </select>
)davis_delimeter";


const char kHtmlComboboxUpdateFooBlock[] = R"davis_delimeter(
function updateBackground(select) {
            var selectedImage = select.options[select.selectedIndex].getAttribute('data-image');
            select.style.backgroundImage = 'url("data:image/svg+xml,' + encodeURIComponent(selectedImage) + '")';
            var selectedOption = select.options[select.selectedIndex].text;
            for(let i=0;i<data.length;++i){
            var obj = data[i];
            switch (selectedOption) {
            case 'line':
            obj.mode='lines';
            break;
            case 'line + point':
            obj.mode='lines+markers';
            break;
            case 'point':
            obj.mode='markers';
            break;
            default: console.log('uknown option');
            }
           }
           Plotly.newPlot('gd', data);
        }

        document.addEventListener('DOMContentLoaded', function() {
            var dropdown = document.getElementById('dropdown');
            updateBackground(dropdown);
        });
)davis_delimeter";


const char kHtmlComboboxSelectSurfaceMatrixBlock[]=R"davis_delimeter(
    <select id="dropdown" onchange="updateBackground(this)">
        <option value="matrix_image" data-image="<?xml version='1.0' encoding='UTF-8' standalone='no'?><!-- Created with Inkscape (http://www.inkscape.org/) --><svg   width='60mm'   height='60mm'   viewBox='0 0 60 60'   version='1.1'   id='svg1'   inkscape:export-filename='matrix.svg'   inkscape:export-xdpi='96'   inkscape:export-ydpi='96'   xmlns:inkscape='http://www.inkscape.org/namespaces/inkscape'   xmlns:sodipodi='http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd'   xmlns='http://www.w3.org/2000/svg'   xmlns:svg='http://www.w3.org/2000/svg'>  <sodipodi:namedview     id='namedview1'     pagecolor='#ffffff'     bordercolor='#000000'     borderopacity='0.25'     inkscape:showpageshadow='2'     inkscape:pageopacity='0.0'     inkscape:pagecheckerboard='0'     inkscape:deskcolor='#d1d1d1'     inkscape:document-units='mm'     inkscape:zoom='0.73139029'     inkscape:cx='118.26791'     inkscape:cy='428.63571'     inkscape:window-width='1920'     inkscape:window-height='1017'     inkscape:window-x='1912'     inkscape:window-y='-8'     inkscape:window-maximized='1'     inkscape:current-layer='layer1' />  <defs     id='defs1' />  <g     inkscape:label='Слой 1'     inkscape:groupmode='layer'     id='layer1'>    <rect       style='fill:#ff2a2a;stroke-width:0.264583'       id='rect1'       width='30'       height='30'       x='0'       y='0' />    <rect       style='fill:#ffff00;stroke-width:0.264583'       id='rect2'       width='30'       height='30'       x='30'       y='0' />    <rect       style='fill:#ff00ff;stroke-width:0.264583'       id='rect3'       width='30'       height='30'       x='30'       y='30' />    <rect       style='fill:#00ffff;stroke-width:0.264583'       id='rect4'       width='30'       height='30'       x='0'       y='30' />  </g></svg>">matrix</option>
        <option value="surface_image" data-image="<?xml version='1.0' encoding='UTF-8' standalone='no'?><!-- Created with Inkscape (http://www.inkscape.org/) --><svg   width='48.685608mm'   height='57.444851mm'   viewBox='0 0 48.685608 57.444851'   version='1.1'   id='svg1'   inkscape:export-filename='matrix.svg'   inkscape:export-xdpi='96'   inkscape:export-ydpi='96'   xmlns:inkscape='http://www.inkscape.org/namespaces/inkscape'   xmlns:sodipodi='http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd'   xmlns='http://www.w3.org/2000/svg'   xmlns:svg='http://www.w3.org/2000/svg'>  <sodipodi:namedview     id='namedview1'     pagecolor='#ffffff'     bordercolor='#000000'     borderopacity='0.25'     inkscape:showpageshadow='2'     inkscape:pageopacity='0.0'     inkscape:pagecheckerboard='0'     inkscape:deskcolor='#d1d1d1'     inkscape:document-units='mm'     inkscape:zoom='0.73139029'     inkscape:cx='118.26791'     inkscape:cy='428.63571'     inkscape:window-width='1920'     inkscape:window-height='1017'     inkscape:window-x='1912'     inkscape:window-y='-8'     inkscape:window-maximized='1'     inkscape:current-layer='layer1' />  <defs     id='defs1' />  <g     inkscape:label='Слой 1'     inkscape:groupmode='layer'     id='layer1'     transform='translate(-5.1280656,-1.0459301)'>    <path       style='fill:#0099ff;fill-opacity:1;stroke-width:0.264583'       d='M 15.257176,8.9730377 5.1280653,39.450809 24.934094,46.052817 Z'       id='path8' />    <path       style='fill:#0099ff;fill-opacity:1;stroke-width:0.264583'       d='M 39.107412,1.0459301 21.435214,27.86359 38.857644,39.366818 Z'       id='path12' />    <path       style='fill:#00d3ff;fill-opacity:1;stroke-width:0.264583'       d='M 15.259243,8.9749767 33.254436,35.200199 24.753217,45.962379 Z'       id='path9'       sodipodi:nodetypes='cccc' />    <path       style='fill:#00d3ff;fill-opacity:1;stroke-width:0.264583'       d='m 39.108907,1.048338 10.594434,29.989119 -10.997004,8.19519 z'       id='path13'       sodipodi:nodetypes='cccc' />    <path       style='fill:#0099ff;fill-opacity:1;stroke-width:0.264583'       d='m 53.813674,29.791115 -31.459079,6.466818 4.185507,20.453528 z'       id='path10' />    <path       style='fill:#00d3ff;fill-opacity:1;stroke-width:0.264583'       d='M 53.813028,29.793875 40.098917,58.49078 26.527985,56.509598 Z'       id='path11'       sodipodi:nodetypes='cccc' />  </g></svg>">surface</option>
    </select>
)davis_delimeter";

const char kHtmlComboboxUpdateSurfaceMatrixFooBlock[]=R"davis_delimeter(
function updateBackground(select) {
            var selectedImage = select.options[select.selectedIndex].getAttribute('data-image');
            select.style.backgroundImage = 'url("data:image/svg+xml,' + encodeURIComponent(selectedImage) + '")';
            var selectedOption = select.options[select.selectedIndex].text;

            switch (selectedOption) {
            case 'matrix':
            data[0].type='heatmap';
            console.log('heatmap');
            break;
            case 'surface':
            data[0].type='surface';
            console.log('surface');
            break;
            default: console.log('uknown option');
            }
           Plotly.newPlot('gd', data, layout, config);
        }

        document.addEventListener('DOMContentLoaded', function() {
            var dropdown = document.getElementById('dropdown');
            updateBackground(dropdown);
        });
)davis_delimeter";

extern const char kHtmlDavisLogoHyperlinkBlock[] = R"davis_delimeter(
<a href="https://devtoolsorganization.github.io/matrix-data-visualization-DAVIS/#/" style = " position: fixed;
                                                                                                 top: 10px;
                                                                                                 left: 20px;
                                                                                                 z-index: 1000;"
    target="_blank" title="about DAVIS">
    <svg xmlns="http://www.w3.org/2000/svg" xml:space="preserve" width="200" height="50" version="1.1"
        style="shape-rendering:geometricPrecision; text-rendering:geometricPrecision; image-rendering:optimizeQuality; fill-rule:evenodd; clip-rule:evenodd"
        viewBox="0 0 16054.2 3274.72" xmlns:xlink="http://www.w3.org/1999/xlink"
        xmlns:xodm="http://www.corel.com/coreldraw/odm/2003">
        <defs>
            <style type="text/css">
                <![CDATA[
                .fil2 {
                    fill: #1699DD;
                    fill-rule: nonzero
                }

                .fil1 {
                    fill: #4BB8F2;
                    fill-rule: nonzero
                }

                .fil3 {
                    fill: #FFA940;
                    fill-rule: nonzero
                }

                .fil0 {
                    fill: #2490D0;
                    fill-rule: nonzero
                }
                ]]>
            </style>
        </defs>
        <g id="Слой_x0020_1">
            <metadata id="CorelCorpID_0Corel-Layer" />
            <path class="fil0"
                d="M3956.64 3274.72c-109.03,0 -207.58,-18.52 -295.64,-55.57 -88.07,-37.04 -158.31,-94.35 -210.72,-171.92 -52.42,-77.58 -78.62,-174.38 -78.62,-290.39 0,-180.32 48.22,-317.3 144.67,-410.96 96.45,-93.65 233.43,-140.47 410.95,-140.47 176.12,0 309.26,45.42 399.43,136.28 90.16,90.86 135.23,222.25 135.23,394.18 0,48.92 -22.36,73.38 -67.09,73.38l-769.49 0c0,92.26 32.15,163.2 96.45,212.81 64.3,49.62 153.76,74.43 268.38,74.43 110.43,0 209.67,-25.16 297.74,-75.48 9.78,-5.59 17.47,-8.38 23.07,-8.38 9.78,0 17.47,6.29 23.06,18.87l50.32 90.17c4.19,8.38 6.29,16.07 6.29,23.06 0,9.79 -6.29,18.87 -18.87,27.26 -57.31,34.95 -119.16,60.81 -185.55,77.58 -66.4,16.77 -142.92,25.16 -229.59,25.16zm262.09 -620.62c0,-86.66 -24.12,-154.46 -72.34,-203.38 -48.22,-48.92 -120.56,-73.39 -217,-73.39 -97.85,0 -172.98,25.17 -225.4,75.48 -52.42,50.32 -78.63,117.42 -78.63,201.29l593.37 0z" />
            <path id="_1" class="fil0"
                d="M5126.59 3243.27c-19.57,0 -34.24,-3.84 -44.02,-11.53 -9.79,-7.68 -19.58,-21.32 -29.36,-40.88l-421.43 -895.29c-4.2,-8.39 -6.29,-16.77 -6.29,-25.17 0,-9.78 3.14,-17.82 9.43,-24.11 6.29,-6.29 15.02,-9.43 26.21,-9.43l174.03 0c18.17,0 31.45,3.14 39.83,9.43 8.39,6.29 16.07,17.82 23.07,34.59l280.96 654.17 280.95 -654.17c6.99,-15.37 15.02,-26.56 24.12,-33.54 9.08,-6.99 22.71,-10.48 40.88,-10.48l174.03 0c11.17,0 19.92,3.14 26.21,9.43 6.29,6.29 9.43,14.32 9.43,24.11 0,8.39 -2.1,16.77 -6.29,25.17l-421.43 895.29c-9.78,19.57 -19.58,33.2 -29.36,40.88 -9.78,7.69 -24.46,11.53 -44.03,11.53l-106.93 0z" />
            <path id="_2" class="fil0"
                d="M6135.11 3243.27c-27.96,0 -48.22,-6.29 -60.81,-18.87 -12.58,-12.58 -18.87,-31.46 -18.87,-56.62l0 -1144.79 -366.92 0c-27.96,0 -47.17,-5.59 -57.66,-16.77 -10.48,-11.18 -15.72,-30.06 -15.72,-56.62l0 -56.61c0,-26.56 5.24,-45.78 15.72,-57.66 10.48,-11.88 29.7,-17.82 57.66,-17.82l1002.22 0c27.96,0 47.52,5.94 58.71,17.82 11.18,11.87 16.77,31.1 16.77,57.66l0 56.61c0,26.56 -5.59,45.43 -16.77,56.62 -11.18,11.18 -30.75,16.77 -58.71,16.77l-366.93 0 0 1144.79c0,25.16 -5.93,44.03 -17.82,56.62 -11.88,12.57 -32.5,18.87 -61.86,18.87l-109.02 0z" />
            <path id="_3" class="fil0"
                d="M7214.9 3274.72c-181.71,0 -321.84,-47.87 -420.39,-143.62 -98.54,-95.75 -147.81,-226.1 -147.81,-391.03 0,-164.94 49.27,-295.29 147.81,-391.03 98.55,-95.75 238.68,-143.62 420.39,-143.62 181.71,0 322.19,47.87 421.43,143.62 99.25,95.75 148.86,226.1 148.86,391.03 0,164.94 -49.62,295.29 -148.86,391.03 -99.24,95.75 -239.72,143.62 -421.43,143.62zm0 -197.09c99.24,0 174.72,-28.66 226.45,-85.96 51.72,-57.31 77.57,-141.18 77.57,-251.6 0,-109.03 -25.86,-191.85 -77.57,-248.46 -51.72,-56.61 -127.21,-84.91 -226.45,-84.91 -97.85,0 -172.98,28.31 -225.4,84.91 -52.42,56.62 -78.63,139.43 -78.63,248.46 0,109.03 26.22,192.55 78.63,250.55 52.42,58.01 127.55,87.02 225.4,87.02z" />
            <path id="_4" class="fil0"
                d="M8464.54 3274.72c-181.71,0 -321.84,-47.87 -420.39,-143.62 -98.54,-95.75 -147.81,-226.1 -147.81,-391.03 0,-164.94 49.27,-295.29 147.81,-391.03 98.55,-95.75 238.68,-143.62 420.39,-143.62 181.71,0 322.19,47.87 421.43,143.62 99.25,95.75 148.86,226.1 148.86,391.03 0,164.94 -49.62,295.29 -148.86,391.03 -99.24,95.75 -239.72,143.62 -421.43,143.62zm0 -197.09c99.24,0 174.72,-28.66 226.45,-85.96 51.72,-57.31 77.57,-141.18 77.57,-251.6 0,-109.03 -25.86,-191.85 -77.57,-248.46 -51.72,-56.61 -127.21,-84.91 -226.45,-84.91 -97.85,0 -172.98,28.31 -225.4,84.91 -52.42,56.62 -78.63,139.43 -78.63,248.46 0,109.03 26.22,192.55 78.63,250.55 52.42,58.01 127.55,87.02 225.4,87.02z" />
            <path id="_5" class="fil0"
                d="M9317.89 3243.27c-27.95,0 -47.87,-6.29 -59.75,-18.87 -11.88,-12.58 -17.82,-31.46 -17.82,-56.62l0 -1272.7c0,-26.56 5.94,-46.12 17.82,-58.71 11.87,-12.57 31.8,-18.87 59.75,-18.87l111.13 0c27.96,0 48.22,6.29 60.8,18.87 12.58,12.58 18.87,32.15 18.87,58.71l0 1272.7c0,25.16 -5.94,44.03 -17.82,56.62 -11.88,12.57 -32.5,18.87 -61.85,18.87l-111.13 0z" />
            <path id="_6" class="fil0"
                d="M10192.22 3274.72c-83.87,0 -165.65,-8.73 -245.32,-26.21 -79.67,-17.47 -148.16,-43.68 -205.47,-78.62 -18.17,-9.78 -27.26,-20.28 -27.26,-31.45 0,-8.39 2.79,-16.07 8.38,-23.07l58.71 -102.74c6.99,-12.58 13.98,-18.87 20.97,-18.87 6.99,0 16.07,3.49 27.26,10.48 41.93,25.16 93.66,46.12 155.16,62.9 61.51,16.77 118.11,25.16 169.84,25.16 79.67,0 136.63,-8.03 170.88,-24.11 34.24,-16.07 51.37,-45.08 51.37,-87.02 0,-23.77 -6.64,-42.98 -19.92,-57.66 -13.28,-14.68 -33.2,-27.61 -59.76,-38.79 -26.56,-11.18 -70.59,-26.56 -132.09,-46.13 0,0 -23.07,-7.68 -69.19,-23.06 -79.68,-26.56 -143.28,-52.42 -190.8,-77.58 -47.52,-25.16 -84.21,-56.96 -110.07,-95.4 -25.86,-38.44 -38.79,-87.02 -38.79,-145.72 0,-95.05 40.18,-167.39 120.56,-217 80.37,-49.62 184.86,-74.43 313.46,-74.43 156.56,0 291.44,33.54 404.67,100.64 18.17,9.78 27.25,20.27 27.25,31.45 0,6.99 -3.49,16.07 -10.48,27.26l-56.61 90.16c-8.38,12.58 -15.37,18.87 -20.97,18.87 -5.59,0 -13.98,-3.49 -25.16,-10.48 -36.35,-22.36 -80.03,-40.18 -131.05,-53.47 -51.02,-13.27 -102.39,-19.92 -154.1,-19.92 -69.89,0 -121.26,7.34 -154.11,22.02 -32.84,14.67 -49.27,42.98 -49.27,84.91 0,36.34 19.22,65 57.66,85.96 38.44,20.97 105.18,46.13 200.24,75.48l69.19 20.97c109.02,34.95 185.55,76.18 229.59,123.71 44.03,47.52 66.05,106.93 66.05,178.22 0,86.66 -38.09,157.26 -114.27,211.76 -76.18,54.52 -188.35,81.77 -336.52,81.77z" />
            <path class="fil1"
                d="M1763.76 1482.07c88.08,87.78 173.48,173.58 263.16,263.73 49.48,50.06 96.24,94.37 139.45,141.91 38.52,42.4 52.26,82.67 14.8,125.38 -52.17,59.5 -107.71,117.11 -168.24,167.84 -41.3,34.61 -75.45,28.26 -117.37,-8.63 -52.26,-45.98 -101.67,-95.22 -152.31,-143.06 -85.44,-85.93 -170.89,-171.86 -258.65,-259.38 -35.96,-35.87 -69.34,-70.41 -103.3,-104.38 -223.12,-223.29 -446.35,-446.45 -669.55,-669.63 -32.37,-32.36 -32.44,-32.37 -65.7,0.88 -119.72,119.69 -239.37,239.47 -359.17,359.08 -44.62,44.55 -78.1,47.95 -124.72,5.84 -48.54,-43.84 -94.5,-90.77 -139.07,-138.69 -30.17,-32.45 -30,-67.91 -4.01,-104.62 10.64,-15.04 23.68,-28.58 36.75,-41.66 340.46,-340.72 681.07,-681.28 1021.67,-1021.87 5.4,-5.4 10.84,-10.79 16.45,-15.98 55.77,-51.53 96.2,-52.05 150.47,0.02 37.81,36.29 74.6,73.67 110.92,111.46 38.19,39.74 54.7,85.35 -2.84,141.11 -123.13,119.32 -242.7,242.3 -364.72,362.78 -19.78,19.54 -22.29,31.61 -1.17,52.61 258.66,257.24 516.44,515.37 777.14,775.25z" />
            <path class="fil2"
                d="M1828.76 1422.64c156.64,-156.85 250.64,-251.47 407.45,-408.16 10.78,-10.76 22.57,-20.69 34.82,-29.75 37.35,-27.63 70.49,-27.08 107.97,1.25 9.57,7.22 19.35,14.41 27.75,22.87 156.96,158.05 318.02,312.33 469.24,475.71 132.17,142.79 235.39,305.17 275.3,501.12 36.11,177.31 4.12,342.91 -82.87,498.53 -120.56,215.69 -290.18,387.11 -494.71,522.72 -155,102.77 -327.03,155.45 -515.03,133.77 -156.01,-17.98 -294.73,-81.25 -423,-171.13 -121.66,-85.25 -221.99,-193.13 -326.44,-296.83 -92.99,-92.33 -185.52,-185.11 -277.99,-277.96 -67.05,-67.33 -67.65,-107.37 -0.83,-174.5 148.68,-149.36 234.97,-237.6 387.53,-388.42 97.13,98.34 183.88,185.22 261.48,261.9 -114.41,114.46 -165.27,165.3 -279.11,279.14 51.2,51.2 98.41,98.03 145.2,145.28 76.02,76.77 150.78,154.83 243.17,213.05 158.58,99.96 321.99,121.58 492.71,31.96 159.63,-83.8 284.77,-207.59 397.8,-345.02 62.83,-76.39 115.09,-159.44 141.26,-255.81 42.65,-156.99 1.36,-299.93 -97.37,-420.33 -97.96,-119.47 -211.49,-226.16 -317.73,-338.9 -19.04,-20.2 -29.58,-5.77 -42.25,6.91 -111.9,112.03 -157.09,165.16 -271.5,275.32 -87.8,-87.59 -175.97,-175.64 -262.86,-262.71z" />
            <path class="fil3"
                d="M1763.76 1482.07c88.08,87.78 173.48,173.58 263.16,263.73 49.48,50.06 96.24,94.37 139.45,141.91 38.52,42.4 52.26,82.67 14.8,125.38 -52.17,59.5 -107.71,117.11 -168.24,167.84 -41.3,34.61 -75.45,28.26 -117.37,-8.63 -52.26,-45.98 -101.67,-95.22 -152.31,-143.06 -85.44,-85.93 -170.89,-171.86 -258.65,-259.38 -35.96,-35.87 -69.34,-70.41 -103.3,-104.38 -223.12,-223.29 -446.35,-446.45 -669.55,-669.63 -32.37,-32.36 -32.44,-32.37 -65.7,0.88 -119.72,119.69 -239.37,239.47 -359.17,359.08 -44.62,44.55 -78.1,47.95 -124.72,5.84 -48.54,-43.84 -94.5,-90.77 -139.07,-138.69 -30.17,-32.45 -30,-67.91 -4.01,-104.62 10.64,-15.04 23.68,-28.58 36.75,-41.66 340.46,-340.72 681.07,-681.28 1021.67,-1021.87 5.4,-5.4 10.84,-10.79 16.45,-15.98 55.77,-51.53 96.2,-52.05 150.47,0.02 37.81,36.29 74.6,73.67 110.92,111.46 38.19,39.74 54.7,85.35 -2.84,141.11 -123.13,119.32 -242.7,242.3 -364.72,362.78 -19.78,19.54 -22.29,31.61 -1.17,52.61 258.66,257.24 516.44,515.37 777.14,775.25z" />
            <path class="fil0"
                d="M1828.76 1422.64c156.64,-156.85 250.64,-251.47 407.45,-408.16 10.78,-10.76 22.57,-20.69 34.82,-29.75 37.35,-27.63 70.49,-27.08 107.97,1.25 9.57,7.22 19.35,14.41 27.75,22.87 156.96,158.05 318.02,312.33 469.24,475.71 132.17,142.79 235.39,305.17 275.3,501.12 36.11,177.31 4.12,342.91 -82.87,498.53 -120.56,215.69 -290.18,387.11 -494.71,522.72 -155,102.77 -327.03,155.45 -515.03,133.77 -156.01,-17.98 -294.73,-81.25 -423,-171.13 -121.66,-85.25 -221.99,-193.13 -326.44,-296.83 -92.99,-92.33 -185.52,-185.11 -277.99,-277.96 -67.05,-67.33 -67.65,-107.37 -0.83,-174.5 148.68,-149.36 234.97,-237.6 387.53,-388.42 97.13,98.34 183.88,185.22 261.48,261.9 -114.41,114.46 -165.27,165.3 -279.11,279.14 51.2,51.2 98.41,98.03 145.2,145.28 76.02,76.77 150.78,154.83 243.17,213.05 158.58,99.96 321.99,121.58 492.71,31.96 159.63,-83.8 284.77,-207.59 397.8,-345.02 62.83,-76.39 115.09,-159.44 141.26,-255.81 42.65,-156.99 1.36,-299.93 -97.37,-420.33 -97.96,-119.47 -211.49,-226.16 -317.73,-338.9 -19.04,-20.2 -29.58,-5.77 -42.25,6.91 -111.9,112.03 -157.09,165.16 -271.5,275.32 -87.8,-87.59 -175.97,-175.64 -262.86,-262.71z" />
            <path class="fil3"
                d="M11170.22 3236.09c-24.67,0 -42.25,-5.55 -52.73,-16.65 -10.48,-11.1 -15.72,-27.75 -15.72,-49.95l0 -1122.95c0,-23.43 5.24,-40.7 15.72,-51.81 10.48,-11.1 28.06,-16.65 52.73,-16.65l370 0c208.43,0 367.84,49.95 478.23,149.85 110.38,99.9 165.58,259.62 165.58,479.15 0,419.33 -214.61,628.99 -643.8,628.99l-370 0zm384.8 -179.45c130.73,0 229.09,-33.92 295.08,-101.75 65.98,-67.83 98.97,-183.76 98.97,-347.79 0,-164.04 -32.99,-279.66 -98.97,-346.88 -65.99,-67.22 -164.35,-100.83 -295.08,-100.83l-216.45 0 0 897.25 216.45 0z" />
            <path id="_1_0" class="fil3"
                d="M12276.51 3236.09c-20.97,0 -31.45,-9.25 -31.45,-27.75 0,-7.4 1.85,-15.42 5.55,-24.04l488.4 -1158.1c7.4,-18.5 15.42,-31.14 24.05,-37.92 8.63,-6.79 20.97,-10.18 37,-10.18l101.75 0c17.27,0 29.91,3.39 37.93,10.18 8.01,6.78 15.72,19.42 23.12,37.92l488.4 1158.1c3.71,8.63 5.56,16.65 5.56,24.04 0,18.5 -10.48,27.75 -31.45,27.75l-160.95 0c-16.03,0 -27.44,-2.15 -34.22,-6.47 -6.79,-4.32 -13.26,-13.27 -19.43,-26.83l-105.45 -259 -510.59 0 -103.6 259c-6.17,13.56 -12.65,22.51 -19.42,26.83 -6.79,4.32 -18.19,6.47 -34.23,6.47l-160.94 0zm769.6 -464.35l-196.1 -484.7 -196.1 484.7 392.2 0z" />
            <path id="_2_1" class="fil3"
                d="M13861.96 3236.09c-17.27,0 -29.91,-3.09 -37.93,-9.25 -8.01,-6.17 -15.72,-18.5 -23.12,-37l-481 -1159.95c-3.7,-7.4 -5.55,-14.8 -5.55,-22.2 0,-8.63 2.77,-15.72 8.32,-21.27 5.56,-5.56 13.27,-8.33 23.13,-8.33l159.1 0c16.04,0 28.37,3.09 37,9.25 8.63,6.17 15.41,16.03 20.35,29.6l349.65 887.99 349.65 -887.99c4.94,-13.57 11.72,-23.43 20.36,-29.6 8.63,-6.17 20.97,-9.25 37,-9.25l159.1 0c9.87,0 17.58,2.77 23.13,8.33 5.55,5.55 8.33,12.64 8.33,21.27 0,7.4 -1.86,14.8 -5.56,22.2l-479.14 1159.95c-7.4,18.5 -15.42,30.83 -24.05,37 -8.63,6.17 -21.59,9.25 -38.85,9.25l-99.89 0z" />
            <path id="_3_2" class="fil3"
                d="M14759.21 3236.09c-24.67,0 -42.25,-5.55 -52.73,-16.65 -10.48,-11.1 -15.72,-27.75 -15.72,-49.95l0 -1122.95c0,-23.43 5.24,-40.7 15.72,-51.81 10.48,-11.1 28.06,-16.65 52.73,-16.65l98.05 0c24.66,0 42.55,5.55 53.65,16.65 11.09,11.1 16.65,28.37 16.65,51.81l0 1122.95c0,22.2 -5.24,38.84 -15.72,49.95 -10.48,11.1 -28.68,16.65 -54.58,16.65l-98.05 0z" />
            <path id="_4_3" class="fil3"
                d="M15595.41 3263.84c-87.57,0 -173.59,-9.56 -258.07,-28.68 -84.48,-19.12 -152.01,-45.94 -202.58,-80.47 -16.03,-11.1 -24.04,-20.97 -24.04,-29.6 0,-8.63 2.47,-16.04 7.4,-22.2l61.05 -96.2c7.4,-11.1 14.19,-16.65 20.36,-16.65 6.17,0 14.18,3.08 24.04,9.24 45.64,27.14 98.66,49.03 159.1,65.68 60.43,16.65 121.48,24.97 183.15,24.97 83.86,0 147.08,-13.88 189.62,-41.62 42.55,-27.75 63.83,-72.46 63.83,-134.13 0,-37 -8.02,-66.61 -24.05,-88.8 -16.03,-22.2 -39.46,-41.31 -70.3,-57.35 -30.83,-16.03 -80.78,-37.62 -149.84,-64.75l-42.55 -16.65c-80.17,-32.07 -146.46,-62.9 -198.87,-92.5 -52.42,-29.6 -95.89,-68.45 -130.43,-116.55 -34.54,-48.1 -51.8,-106.68 -51.8,-175.75 0,-112.23 42.86,-198.87 128.57,-259.92 85.71,-61.05 198.25,-91.57 337.62,-91.57 85.1,0 158.79,8.01 221.08,24.05 62.28,16.03 116.24,40.69 161.88,74 14.8,11.09 22.2,21.58 22.2,31.45 0,7.4 -2.47,14.18 -7.4,20.35l-59.2 96.2c-7.4,11.1 -13.57,16.66 -18.51,16.66 -4.93,0 -12.94,-3.71 -24.04,-11.1 -78.94,-50.57 -176.98,-75.85 -294.15,-75.85 -77.7,0 -136.28,14.18 -175.74,42.55 -39.46,28.36 -59.2,73.38 -59.2,135.05 0,38.23 8.32,68.75 24.98,91.57 16.65,22.82 41.01,42.24 73.07,58.27 32.07,16.04 83.87,37.62 155.41,64.76l46.25 18.5c90.03,35.77 160.33,68.76 210.9,98.97 50.57,30.22 89.73,67.83 117.47,112.85 27.75,45.01 41.63,102.68 41.63,172.97 0,106.07 -39.78,189.63 -119.33,250.68 -79.55,61.05 -192.71,91.57 -339.47,91.57z" />
        </g>
    </svg>
</a>
)davis_delimeter";


const char kAverageButtonStyleBlock[] = R"davis_delimeter(
<style>
        .toggle-button {
            display: inline-block;
            width: 60px;
            height: 30px;
            background-color: #ccc;
            border-radius: 15px;
            position: relative;
            cursor: pointer;
        }
        .toggle-button::before {
            content: '';
            position: absolute;
            width: 26px;
            height: 26px;
            background-color: #fff;
            border-radius: 50%;
            top: 2px;
            left: 2px;
            transition: transform 0.3s;
        }
        .toggle-button.active {
            background-color: #4caf50;
        }
        .toggle-button.active::before {
            transform: translateX(30px);
        }
        .state-text {
            margin-top: 10px;
            font-size: 18px;
        }
</style>
)davis_delimeter";

const char kAverageButtonDivBlock[] = R"davis_delimeter(
<div class="toggle-button" id="toggleButton"></div>
    <div class="state-text" id="stateText">Average: OFF</div>
)davis_delimeter";


const char kAverageButtonJsFooBlock[] = R"davis_delimeter(
 const toggleButton = document.getElementById('toggleButton');
        const stateText = document.getElementById('stateText');

        toggleButton.addEventListener('click', () => {
            toggleButton.classList.toggle('active');
            const isActive = toggleButton.classList.contains('active');
            stateText.textContent = `Average: ${isActive ? 'ON' : 'OFF'}`;
            if(isActive){temp = data; data = average;}else{data = temp;};
            Plotly.newPlot('gd', data);
            console.log('Toggle button state:', isActive);
        });
)davis_delimeter";


const char kAverageErrorDataBlock[] = R"davis_delimeter(
    x: [%1],
    y: [%2],
    type: 'scatter',
    fill: "tozerox",
    fillcolor: "rgba(231,107,243,0.2)",
    line: {color: "transparent"},
    showlegend: false
)davis_delimeter";

// *INDENT-ON*
//#STOP_GRAB_TO_DVS_NAMESPACE
} // namespace dvs
