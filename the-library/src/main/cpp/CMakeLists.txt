file(
  GLOB_RECURSE
  learn_cpp.project_structure.the_library.MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp)

#REM: ===== Static library =====
add_library(
  ${PROJECT_NAME}-static
  STATIC
  ${learn_cpp.project_structure.the_library.MAIN_SOURCES})
add_library(
  learn_cpp.project_structure::${PROJECT_NAME}-static
  ALIAS
  ${PROJECT_NAME}-static)
target_compile_definitions(
  ${PROJECT_NAME}-static
  PUBLIC LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC
  PRIVATE LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_BUILD)
set_target_properties(
  ${PROJECT_NAME}-static
  PROPERTIES
  OUTPUT_NAME "${learn_cpp.project_structure.the_library.GENEXP_OUTPUT_NAME}")
target_include_directories(
  ${PROJECT_NAME}-static
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/include>)

#REM: ===== Shared library =====
set(BUILD_SHARED_LIBS ON)
add_library(
  ${PROJECT_NAME}-shared
  SHARED
  ${learn_cpp.project_structure.the_library.MAIN_SOURCES})
add_library(
  learn_cpp.project_structure::${PROJECT_NAME}-shared
  ALIAS
  ${PROJECT_NAME}-shared)
target_compile_definitions(
  ${PROJECT_NAME}-shared
  PRIVATE LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_BUILD)
set_target_properties(
  ${PROJECT_NAME}-shared
  PROPERTIES
  OUTPUT_NAME "${learn_cpp.project_structure.the_library.GENEXP_OUTPUT_NAME}")
target_include_directories(
  ${PROJECT_NAME}-shared
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/include>)

#REM: ===== Install rules =====
install(
  TARGETS
    ${PROJECT_NAME}-static
    ${PROJECT_NAME}-shared
  EXPORT ${PROJECT_NAME}-targets
  LIBRARY DESTINATION 
    ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/lib
    COMPONENT library
  ARCHIVE DESTINATION  
    ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/lib
    COMPONENT library
  RUNTIME DESTINATION 
    ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/bin
    COMPONENT library)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/public/
  DESTINATION ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/include
  COMPONENT library
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tpp")

install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE learn_cpp.project_structure::
  DESTINATION ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/lib/cmake/${PROJECT_NAME}
  COMPONENT library)

#REM: ===== Package config files (generated in binary tree) =====
include(CMakePackageConfigHelpers)

file(MAKE_DIRECTORY ${learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR})

write_basic_package_version_file(
  ${learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

file(WRITE
  ${learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR}/${PROJECT_NAME}-config.cmake
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")\n")

install(
  FILES
    ${learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR}/${PROJECT_NAME}-config.cmake
    ${learn_cpp.project_structure.the_library.CMAKE_GENERATED_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION 
    ${learn_cpp.project_structure.the_library.INSTALL_INFIX_DIR}/lib/cmake/${PROJECT_NAME}
  COMPONENT library)