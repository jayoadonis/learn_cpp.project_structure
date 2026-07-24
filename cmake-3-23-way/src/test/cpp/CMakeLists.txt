file(GLOB_RECURSE
  learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_CXX_TEST_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp)

add_executable(${PROJECT_NAME}_target_test_app)

set_target_properties(${PROJECT_NAME}_target_test_app
  PROPERTIES
  OUTPUT_NAME cmake-3.23-way)

target_compile_options(${PROJECT_NAME}_target_test_app
  PRIVATE
  $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/UNDEBUG>
  $<$<AND:$<CONFIG:Release>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-UNDEBUG>)

target_sources(${PROJECT_NAME}_target_test_app
  PRIVATE
  ${learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_CXX_TEST_SOURCES}

  # REM: [KEYPOINT] Private headers are internal implementation details
  PRIVATE FILE_SET private_header_test_sources
  TYPE HEADERS
  BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/private

  # REM: Omitted FILES as intended
)

# list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/install")
# find_package("cmake-3-23-way" 0.1.0 REQUIRED)

target_link_libraries(${PROJECT_NAME}_target_test_app
  PRIVATE
  learn_cpp.project_structure::cmake-3-23-way_target_main_lib)

add_custom_command(
  TARGET 
  ${PROJECT_NAME}_target_test_app POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:learn_cpp.project_structure::cmake-3-23-way_target_main_lib>
  $<TARGET_FILE_DIR:${PROJECT_NAME}_target_test_app>)

add_test(NAME ${PROJECT_NAME}_unit_test
  COMMAND ${PROJECT_NAME}_target_test_app unit)

set_tests_properties(${PROJECT_NAME}_unit_test
  PROPERTIES LABELS "unit_test")

add_test(NAME ${PROJECT_NAME}_integration_test
  COMMAND ${PROJECT_NAME}_target_test_app integration)

set_tests_properties(${PROJECT_NAME}_integration_test
  PROPERTIES LABELS "integration_test")