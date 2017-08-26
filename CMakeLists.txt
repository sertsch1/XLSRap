# CMake required version
cmake_minimum_required(VERSION 3.4)

# "Only interpret if() arguments as variables or keywords when unquoted."
cmake_policy(SET CMP0054 NEW)

# Set cmake build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Set project title
project(xlsrap)

# Base path constants
set(XLSRAP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(XLSRAP_BIN_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(XLSRAP_BIN_OUT_DIR ${CMAKE_BINARY_DIR}/build)

# Externals
set(XLSRAP_EXTERNAL ${XLSRAP_ROOT}/externals)

# Module
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${XLSRAP_ROOT}/build/cmake
)

# Externals
include(Externals)

# Add src
add_subdirectory(src)
