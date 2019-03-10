# QTCanvas Demo Project
# Date: March 9, 2019
# Author: Micah Folsom
# Copyright (C) Micah Folsom, All Rights Reserved.
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(qtcanvas)

# Pull in ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

# Qt setup
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

# Set up local stuff
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS
  "-W -Wall -Wextra -pedantic -fPIC -pthread -m64 -std=c++11")
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
qt5_wrap_cpp(MOCS ${HEADERS})

# Compile the demo app
add_executable(QTCanvasDemo ${SOURCES} ${MOCS})
qt5_use_modules(QTCanvasDemo Widgets)
target_link_libraries(QTCanvasDemo ${CMAKE_CXX_FLAGS} ${ROOT_LIBRARIES})
