cmake_minimum_required(VERSION 3.24...3.30)
project(the-library
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build Type" FORCE)
endif()

set(project.GROUP "learn_cpp.project_structure")
set(project.NAME "${PROJECT_NAME}")
string(STRIP
  "${project.NAME}" project.NAME)
string(REGEX REPLACE "[ _.]" "-"
  project.NAME "${project.NAME}")
string(TOLOWER
  "${project.NAME}" project.NAME)
set(project.VERSION "${PROJECT_VERSION}")

option(LCXX_PS_THELIBRARY_SHARED "Toggle shared" OFF)
option(LCXX_PS_THELIBRARY_FAILWARN "Toggle fail on warn" OFF)

# option(LCXX_PS_THELIBRARY_MAIN_FAILWARN "Toggle fail on warn" OFF)
# option(LCXX_PS_THELIBRARY_TEST_FAILWARN "Toggle fail on warn" OFF)
if(LCXX_PS_THELIBRARY_SHARED)
  set(project.TARGET_MAIN_TYPE "SHARED")
else()
  set(project.TARGET_MAIN_TYPE "STATIC")
endif()

set(project.TARGET_MAIN_NAME
  "${project.NAME}_main_${project.TARGET_MAIN_TYPE}")
string(TOLOWER
  "${project.TARGET_MAIN_NAME}" project.TARGET_MAIN_NAME)

set(project.TARGET_TEST_TYPE "EXECUTABLE")
set(project.TARGET_TEST_NAME
  "${project.NAME}_test_${project.TARGET_TEST_TYPE}")
string(TOLOWER
  "${project.TARGET_TEST_NAME}" project.TARGET_TEST_NAME)

# set(project.TARGET_MAIN_INSTALL_EXPORT_FILENAME
# "${project.NAME}-${project.TARGET_MAIN_TYPE}")
# string(TOLOWER "${project.TARGET_MAIN_INSTALL_EXPORT_FILENAME}"
# project.TARGET_MAIN_INSTALL_EXPORT_FILENAME )
include(CTest)

add_subdirectory("src/main/cpp")

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory("src/test/cpp")
endif()

set(CPACK_VERBATIM_VARIABLES TRUE)
set(CPACK_PACKAGE_VENDOR "${project.GROUP}")
set(CPACK_PACKAGE_NAME "${project.NAME}")
set(CPACK_PACKAGE_VERSION "${project.VERSION}")
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/cpack-options.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cpack-options.cmake"
  @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/cpack-options.cmake")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)