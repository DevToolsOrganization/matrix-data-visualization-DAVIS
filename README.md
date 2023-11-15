![Workflow](https://github.com/valvals/devtools/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)
# devtools
DAVIS is utility for data visualization
The visualization is based on Plotly javascript https://plotly.com/
So DAVIS generate html page with injected data from code
or from file and after that launch browser to show it
Also DAVIS allows some additional functionality to work with data (saving as a file, etc.)

# CLI (command line interface)
  davis [OPTION...]

 -l, --linechart arg  linechart values
 -m, --heatmap arg    heatmap values
 -h, --help           davis commands

Examples how to show davis:

```javascript
davis --heatmap="9,0,8;89,7,6"
copyCodeBlock(anHtmlFile, options);

```javascript
davis -m "7,4,5,6,7;9,6,5,40,3"
copyCodeBlock(anHtmlFile, options);

```javascript
davis -l "6,7,9,54"
copyCodeBlock(anHtmlFile, options);
