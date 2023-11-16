cmake_minimum_required(VERSION 3.14)
set(projectName "davis")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(WIN32)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    endif()
endif(WIN32)

add_subdirectory("ResourceManager")
add_subdirectory(plotly_maker)
add_subdirectory(array_core)
add_subdirectory(common_utils)

# tests
enable_testing()
add_subdirectory(Tests)

include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})
rm_embed_resources(RESOURCES "plotly_maker/plotly-2.27.0.min.js")


add_executable(${projectName} main.cpp cxxopts.hpp ${RESOURCES})
target_link_libraries(${projectName} "ArrayCore")





