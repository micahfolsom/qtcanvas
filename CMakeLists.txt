# QTCanvas Demo Project
# Date: March 9, 2019
# Author: Micah Folsom
# Copyright (C) Micah Folsom, All Rights Reserved.
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(qtcanvas)

# Pull in ROOT
find_package(ROOT 6.16 CONFIG REQUIRED)

# Qt setup
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

# Set up local stuff
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS
  "-W -Wall -Wextra -pedantic -fPIC -pthread -m64 -std=c++17")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
qt5_wrap_cpp(MOCS ${HEADERS})

# Compile the demo app
add_executable(QTCanvasDemo ${SOURCES} ${MOCS})
qt5_use_modules(QTCanvasDemo Widgets)
target_link_libraries(QTCanvasDemo ${CMAKE_CXX_FLAGS} ROOT::Gpad)
