set(projectName "ArrayCore")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(WIN32)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    endif()
endif(WIN32)
set(SOURCE_FILES
    "../common_utils/common_utils.cpp"
    "../common_utils/common_constants.cpp"
    "../plotly_maker/plotly_maker.cpp"
    "../plotly_maker/html_parts.cpp"
    "configurator.cpp"
    )
set(HEADER_FILES
    "../common_utils/common_utils.h"
    "../common_utils/common_constants.h"
    "../plotly_maker/plotly_maker.h"
    "../plotly_maker/html_parts.h"
    "array_core.h"
    "configurator.h"
    )
add_library(${projectName} ${SOURCE_FILES} ${HEADER_FILES})
include_directories(${CMAKE_SOURCE_DIR})
