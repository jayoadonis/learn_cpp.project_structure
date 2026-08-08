cmake_minimum_required(VERSION 3.16)
project("project_structure"
  VERSION "0.1.0"
  LANGUAGES "CXX")

add_subdirectory("the-library")
add_subdirectory("the-application")
add_subdirectory("the-library-module")
add_subdirectory("the-application-module")
add_subdirectory("cmake-3-23-way")

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENT_NO_NAME ON)

include(CPack)