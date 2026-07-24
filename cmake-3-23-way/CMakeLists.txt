cmake_minimum_required(VERSION 3.23)
project(cmake-3-23-way
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

include(CTest)

add_subdirectory(src/main/cpp)

if(BUILD_TESTING)
  add_subdirectory(src/test/cpp)
endif()

include(CPack)