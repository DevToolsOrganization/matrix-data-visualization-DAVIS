cmake_minimum_required(VERSION 3.5)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets QUIET)
if(NOT QT_FOUND)
message("WARNING -----------------------> QT libs is not installed!")
return()
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        ../davis_one/davis.h
        ../davis_one/davis.cpp
        davis_gui.cpp
        davis_gui.h
        about_window.h
        about_window.cpp
        davis_gui.ui
        about_window.ui
)

qt5_add_resources(PROJECT_SOURCES res.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gui

        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(gui SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#qt_add_executable(gui
# ${PROJECT_SOURCES}
#    )
#else()
#add_executable(gui
#    WIN32
#        ${PROJECT_SOURCES}
#    )
#endif()
target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
