include(GNUInstallDirs)

file(GLOB_RECURSE
  project.PRIVATE_CXX_TEST_SOURCES
  CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.c"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.cxx"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.h"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.hxx"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private/*.tpp")

add_executable("${project.TARGET_TEST_NAME}")

set_target_properties("${project.TARGET_TEST_NAME}"
  PROPERTIES
  OUTPUT_NAME "$<LOWER_CASE:${project.NAME}-${project.VERSION}-$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}>"
  
  RUNTIME_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_TEST_TYPE}/${CMAKE_INSTALL_BINDIR}"
  LIBRARY_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_TEST_TYPE}/${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_TEST_TYPE}/${CMAKE_INSTALL_LIBDIR}"
  
  CXX_EXTENSIONS OFF
  
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
  
  COMPILE_WARNING_AS_ERROR "${LCXX_PS_THELIBRARY_FAILWARN}")

target_compile_features("${project.TARGET_TEST_NAME}"
  PUBLIC cxx_std_17)

target_compile_options("${project.TARGET_TEST_NAME}"
  PRIVATE
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->"
  "$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra>")

target_sources("${project.TARGET_TEST_NAME}"
  PRIVATE
  "${project.PRIVATE_CXX_TEST_SOURCES}")

target_include_directories("${project.TARGET_TEST_NAME}"
  PRIVATE
  "${PROJECT_SOURCE_DIR}/src/test/cpp/private")

target_link_libraries("${project.TARGET_TEST_NAME}"
  PRIVATE
  "${project.GROUP}::${project.TARGET_MAIN_NAME}_interface")