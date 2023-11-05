include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows specific, for googletest


include_directories(${RESOURCE_MANAGER_INCLUDE_DIRS})
rm_embed_resources(RESOURCES "res/plotly-2.27.0.min.js")

add_executable(${PROJECT_NAME}_tests PlotlyLibTest.cpp ${RESOURCES})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE PlotlyMaker)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ArrayCore)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE CommonUtils)


include_directories(${CMAKE_SOURCE_DIR})
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
