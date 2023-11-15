set(projectName "ArrayCore")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(WIN32)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif(WIN32)
set(SOURCE_FILES
    "../common_utils/common_utils.cpp"
    "../common_utils/common_constants.cpp"
    "../plotly_maker/plotly_maker.cpp"
    "../plotly_maker/html_parts.cpp"
    )
set(HEADER_FILES
    "../common_utils/common_utils.cpp"
    "../common_utils/common_constants.cpp"
    "../plotly_maker/plotly_maker.cpp"
    "../plotly_maker/html_parts.cpp"
    "array_core.h"
    )
add_library(${projectName} ${SOURCE_FILES} ${HEADER_FILES})
include_directories(${CMAKE_SOURCE_DIR})
