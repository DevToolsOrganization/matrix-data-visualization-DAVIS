set(projectName "PlottyMaker")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCE_FILES
    "plotty_maker.cpp"
    )
set(HEADER_FILES
    "plotty_maker.h"
    )
add_library(${projectName} ${SOURCE_FILES} ${HEADER_FILES})

