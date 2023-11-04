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
add_library(${projectName} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE CommonUtils)
include_directories(${CMAKE_SOURCE_DIR})
