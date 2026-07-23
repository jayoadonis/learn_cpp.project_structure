cmake_minimum_required(VERSION 3.16)
project("the-library"
  VERSION "0.1.0"
  LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

set(learn_cpp.project_structure.the_library.GENEXP_OUTPUT_NAME
  $<LOWER_CASE:${PROJECT_NAME}-${PROJECT_VERSION}-$<CONFIG>-$<PLATFORM_ID>>)

set(learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR
  ${PROJECT_NAME}/${PROJECT_VERSION})
  
set(learn_cpp.project_structure.the_library.GENEXP_INSTALL_SUFFIX_CONFIG_DIR
  $<IF:$<CONFIG:Debug>,/debug,>)

set(learn_cpp.project_structure.the_library.INSTALL_DIR 
  "${CMAKE_SOURCE_DIR}/install" 
  CACHE PATH "INSTALL_PREFIX_PATH" FORCE)

set(learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR
  ${PROJECT_SOURCE_DIR}/cmake/.generate/learn_cpp.project_structure.the_library)

add_subdirectory("src/main/cpp")