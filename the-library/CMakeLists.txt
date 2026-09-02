cmake_minimum_required(VERSION 3.24...3.30)
project(the-library
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/jayoadonis/learn_cpp.project_structure/tree/main/the-library"
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
set(project.DESCRIPTION "${PROJECT_DESCRIPTION}")
set(project.HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")

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
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${project.DESCRIPTION}") 
# set(CPACK_PACKAGE_DESCRIPTION_FILE "path/to/README.md")
# set(CPACK_PACKAGE_CONTACT "sample@sample.contact")
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/cpack-options.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cpack-options.cmake"
  @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/cpack-options.cmake")
if(WIN32)
  set(CPACK_GENERATOR "ZIP;WIX;NSIS") #[[REM: WIX [.msi](dotnet tool install --global wix) or NSIS [.exe](winget install -e --id NSIS.NSIS)]]
  set(CPACK_WIX_VERSION "4") #REM: wix point to wix4+ 'wix.exe' not the legacy wix3 'candle.exe'
elseif(APPLE)
  set(CPACK_GENERATOR "TGZ;DragNDrop")
else()
  set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)     #REM: For ZIP/TGZ splitting
#REM: Native cpack generator configs
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")   #REM: "devel" == "development"
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_COMPONENT_INSTALL ON)      #REM: For DEB splitting
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_COMPONENT_INSTALL ON)         #REM: For RPM splitting
# set(CPACK_RESOURCE_FILE_LICENSE "path/to/OVERALL_LICENSE.txt")
include(CPack)

cmake_host_system_information(RESULT system.TOTAL_RAM 
  QUERY TOTAL_PHYSICAL_MEMORY)
cmake_host_system_information(RESULT system.CPU_CORES 
  QUERY NUMBER_OF_PHYSICAL_CORES)

add_custom_target(check-info
  COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
  COMMAND ${CMAKE_COMMAND} -E echo "PROJECT INFORMATION:"
  COMMAND ${CMAKE_COMMAND} -E echo "  Project Vendor:       ${project.GROUP}"
  COMMAND ${CMAKE_COMMAND} -E echo "  Project Name:         ${project.NAME}"
  COMMAND ${CMAKE_COMMAND} -E echo "  Project Version:      ${project.VERSION}"
  COMMAND ${CMAKE_COMMAND} -E echo "  Project Description:  \"${project.DESCRIPTION}\""
  COMMAND ${CMAKE_COMMAND} -E echo "  Project Homepage URL: ${project.HOMEPAGE_URL}"
  COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
  COMMAND ${CMAKE_COMMAND} -E echo "BUILD ENVIRONMENT:"
  COMMAND ${CMAKE_COMMAND} -E echo "  CMake Generator:      ${CMAKE_GENERATOR}"
  COMMAND ${CMAKE_COMMAND} -E echo "  CMake Version:        ${CMAKE_VERSION}"
  COMMAND ${CMAKE_COMMAND} -E echo "  Build Type:           $<CONFIG>"
  COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
  COMMAND ${CMAKE_COMMAND} -E echo "COMPILER INFORMATION:"
  COMMAND ${CMAKE_COMMAND} -E echo "  C++ Compiler ID:      ${CMAKE_CXX_COMPILER_ID}"
  COMMAND ${CMAKE_COMMAND} -E echo "  Compiler Version:     ${CMAKE_CXX_COMPILER_VERSION}"
  COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
  COMMAND ${CMAKE_COMMAND} -E echo "SYSTEM INFORMATION:"
  COMMAND ${CMAKE_COMMAND} -E echo "  System Name:          ${CMAKE_SYSTEM_NAME}"
  COMMAND ${CMAKE_COMMAND} -E echo "  System Processor:     ${CMAKE_SYSTEM_PROCESSOR}"
  COMMAND ${CMAKE_COMMAND} -E echo "  System Total RAM:     ${system.TOTAL_RAM} MiB"
  COMMAND ${CMAKE_COMMAND} -E echo "  System CPU Cores:     ${system.CPU_CORES}"
  COMMAND ${CMAKE_COMMAND} -E echo "---------------------------------------"
  VERBATIM
  COMMENT "Retrieving project and system diagnostics...")