include(GNUInstallDirs)
include(CmakePackageConfigHelpers)

file(GLOB_RECURSE
  project.PRIVATE_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  # "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.cc"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.cxx"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.h"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.hxx"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private/*.tpp")

file(GLOB_RECURSE
  project.PUBLIC_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  # "${CMAKE_CURRENT_SOURCE_DIR}/public/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/public/*.h"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/public/*.hxx"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/public/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/public/*.tpp")

add_library("${project.TARGET_MAIN_NAME}" "${project.TARGET_MAIN_TYPE}")
add_library("${project.GROUP}::${project.TARGET_MAIN_NAME}"
  ALIAS "${project.TARGET_MAIN_NAME}")

if(BUILD_TESTING)
  #REM: It is intended to be consumed by the testing suite, we did these because of the main private headers
  add_library("${project.TARGET_MAIN_NAME}_interface" INTERFACE)
  add_library("${project.GROUP}::${project.TARGET_MAIN_NAME}_interface"
    ALIAS "${project.TARGET_MAIN_NAME}_interface")
  target_include_directories("${project.TARGET_MAIN_NAME}_interface"
    INTERFACE "${PROJECT_SOURCE_DIR}/src/main/cpp/private")
  target_link_libraries("${project.TARGET_MAIN_NAME}_interface"
    INTERFACE "${project.GROUP}::${project.TARGET_MAIN_NAME}")
endif()

set_target_properties("${project.TARGET_MAIN_NAME}"
  PROPERTIES 
  OUTPUT_NAME "$<LOWER_CASE:${project.NAME}-${project.VERSION}-$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}>"

  RUNTIME_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_MAIN_TYPE}/${CMAKE_INSTALL_BINDIR}"
  LIBRARY_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_MAIN_TYPE}/${CMAKE_INSTALL_LIBDIR}>"
  ARCHIVE_OUTPUT_DIRECTORY "$<CONFIG>/${project.TARGET_MAIN_TYPE}/${CMAKE_INSTALL_LIBDIR}"
  
  CXX_EXTENSIONS OFF
  
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
  
  COMPILE_WARNING_AS_ERROR "${LCXX_PS_THELIBRARY_FAILWARN}")

target_compile_features("${project.TARGET_MAIN_NAME}"
  PUBLIC cxx_std_17)

if(LCXX_PS_THELIBRARY_SHARED)
  target_compile_definitions("${project.TARGET_MAIN_NAME}"
    PRIVATE "LCXX_PS_THELIBRARY_BUILD_SHARED")
else()
  target_compile_definitions("${project.TARGET_MAIN_NAME}"
    PUBLIC "LCXX_PS_THELIBRARY_BUILD_STATIC")
endif()

target_compile_options("${project.TARGET_MAIN_NAME}"
  PRIVATE
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->"
  "$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra>")

target_sources("${project.TARGET_MAIN_NAME}"
  PRIVATE
  "${project.PRIVATE_CXX_MAIN_SOURCES}"
  PUBLIC
  FILE_SET public_cxx_main_sources
  TYPE HEADERS 
  BASE_DIRS "${PROJECT_SOURCE_DIR}/src/main/cpp/public"
  FILES ${project.PUBLIC_CXX_MAIN_SOURCES})

target_include_directories("${project.TARGET_MAIN_NAME}"
  PRIVATE
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private")

install(TARGETS
  "${project.TARGET_MAIN_NAME}"
  EXPORT "${project.NAME}_targets"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  COMPONENT "${project.NAME}_install_component"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT "${project.NAME}_install_component"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT "${project.NAME}_install_component"
  FILE_SET public_cxx_main_sources
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  COMPONENT "${project.NAME}_install_component")

install(EXPORT
  "${project.NAME}_targets"
  NAMESPACE "${project.GROUP}::"
  FILE "${project.TARGET_MAIN_NAME}-targets.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${project.TARGET_MAIN_NAME}"
  COMPONENT "${project.NAME}_install_component")

file(WRITE
  "${CMAKE_CURRENT_BINARY_DIR}/${project.TARGET_MAIN_NAME}-config.cmake"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/${project.TARGET_MAIN_NAME}-targets.cmake\")")

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${project.TARGET_MAIN_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${project.TARGET_MAIN_NAME}-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${project.TARGET_MAIN_NAME}-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${project.TARGET_MAIN_NAME}"
  COMPONENT "${project.NAME}_install_component")