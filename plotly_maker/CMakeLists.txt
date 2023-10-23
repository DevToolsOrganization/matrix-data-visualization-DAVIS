set(projectName "PlotlyMaker")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCE_FILES
    "plotly_maker.cpp"
    )
set(HEADER_FILES
    "plotly_maker.h"
    )
set(RESOURCE_FILES plotly-2.27.0.min.js)
add_library(${projectName} ${SOURCE_FILES} ${HEADER_FILES})

