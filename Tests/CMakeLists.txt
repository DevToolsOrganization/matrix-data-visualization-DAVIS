include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows specific, for googletest

add_executable(${PROJECT_NAME}_tests PlotlyLibTest.cpp)
add_executable(${PROJECT_NAME}_core_tests ArrayCoreTest.cpp)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE PlotlyMaker)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ArrayCore)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE CommonUtils)

target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE PlotlyMaker)
target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE ArrayCore)
target_link_libraries(${PROJECT_NAME}_core_tests PRIVATE CommonUtils)



include_directories(${CMAKE_SOURCE_DIR})
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

# Copy plotly java script to tests
add_custom_command(
        TARGET  ${PROJECT_NAME}_core_tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/plotly_maker/plotly-2.27.0.min.js
                ${CMAKE_CURRENT_BINARY_DIR}/davis_htmls/plotly-2.27.0.min.js
                  )
