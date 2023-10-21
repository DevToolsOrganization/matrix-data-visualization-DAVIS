cmake_minimum_required(VERSION 3.14)
set(projectName "DAVI")
project(${projectName} VERSION 0.01 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(plotty_maker)

add_executable(${projectName} main.cpp)
target_link_libraries(${projectName} PRIVATE PlottyMaker)

