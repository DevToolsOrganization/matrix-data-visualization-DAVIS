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

Example how to show heatmap:
davis --heatmap="9,0,8;89,7,6"
or
davis -m "7,4,5,6,7;9,6,5,40,3"

Example how to show linear chart:
davis --linechart="6,7,9,54"
or
davis -l "6,7,9,54"
