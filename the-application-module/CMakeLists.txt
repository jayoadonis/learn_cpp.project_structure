cmake_minimum_required(VERSION 3.28)
project("the-application-module"
  VERSION "0.1.0"
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#REM: Work only with single config generator, with the exception with 'Ninja Multi-Config' or alike.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

set(learn_cpp.the_application_module.CMAKE_GENEXP_OUTPUT_NAME
  "$<LOWER_CASE:${PROJECT_NAME}-${PROJECT_VERSION}-$<CONFIG>-$<PLATFORM_ID>>")

set(learn_cpp.the_application_module.CMAKE_INSTALL_INFIX_DIR
  "${PROJECT_NAME}/${PROJECT_VERSION}")

add_subdirectory("src/main/cpp")
