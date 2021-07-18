cmake_minimum_required(VERSION 3.14)

project(qt_pr_fifth LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(qt_pr_fifth
    baziercurve.h
    baziercurve.cpp
    main.cpp
    )
target_link_libraries(qt_pr_fifth Qt${QT_VERSION_MAJOR}::Widgets)
