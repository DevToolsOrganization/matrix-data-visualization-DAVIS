include(FetchContent)
include(CMakePrintHelpers)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows specific, for googletest

# Copy plotly java script to tests
MESSAGE("_____________________ Copy Plotlylib to Tests step ___________________________________________")
cmake_print_variables(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/plotly_maker/plotly-2.27.0.min.js DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}/Debug/davis_htmls)

add_executable(${PROJECT_NAME}_plotly_tests PlotlyLibTest.cpp)
target_link_libraries(${PROJECT_NAME}_plotly_tests PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME}_plotly_tests PRIVATE ArrayCore)

add_executable(${PROJECT_NAME}_core_tests ArrayCoreTest.cpp)
target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE ArrayCore)

add_custom_target(_core_tests ALL DEPENDS plotly-2.27.0.min.js)

include_directories(${CMAKE_SOURCE_DIR})
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_plotly_tests _core_tests)


