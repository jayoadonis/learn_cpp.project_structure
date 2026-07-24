file(GLOB_RECURSE
  learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp)

#REM: [KEYPOINT] Private headers are internal implementation details (omitted intended)
# file(GLOB_RECURSE
#   learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_HEADER_MAIN_SOURCES
#   CONFIGURE_DEPENDS
#   ${CMAKE_CURRENT_SOURCE_DIR}/private/*.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/private/*.hpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/private/*.tpp)

file(GLOB_RECURSE
  learn_cpp.project_structure.cmake_3_23_way.CMAKE_PUBLIC_HEADER_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.tpp)

# add_library(${PROJECT_NAME}_target_main_static STATIC)
add_library(${PROJECT_NAME}_target_main_lib
  ${CMAKE_3_23_WAY_LIB_TYPE})

add_library(learn_cpp.project_structure::${PROJECT_NAME}_target_main_lib
  ALIAS ${PROJECT_NAME}_target_main_lib)

set_target_properties(${PROJECT_NAME}_target_main_lib
  PROPERTIES
  OUTPUT_NAME cmake-3.23-way
  #REM: Tell CMake to hide all symbols by default
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}_target_main_lib
  BASE_NAME CMAKE_3_23_WAY
  EXPORT_FILE_NAME 
    ${CMAKE_CURRENT_BINARY_DIR}/.generate/include/cmake_3_23_way_export.h
  EXPORT_MACRO_NAME CMAKE_3_23_WAY_API
  DEPRECATED_MACRO_NAME CMAKE_3_23_WAY_DEPRECATED)

#REM: *_STATIC_DEFINE
#REM: *_EXPORT
#REM: *_NO_EXPORT
#REM: *_DEPRECATED
#REM: *_DEPRECATED_EXPORT
#REM: *_NO_DEPRECATED
if(NOT CMAKE_3_23_WAY_TOGGLE_SHARED)
  target_compile_definitions(${PROJECT_NAME}_target_main_lib
    PRIVATE CMAKE_3_23_WAY_STATIC_DEFINE)
endif()

if(NOT MSVC)
  #REM: ----------------------------------------------------------
  #REM: GCC / CLANG (MSYS64 UCRT64 toolchain)
  #REM: ----------------------------------------------------------
  target_compile_options(
    ${PROJECT_NAME}_target_main_lib
    PRIVATE
    -pedantic-errors    #REM: Reject non-standard C++ extensions (Enforce ISO rules)
    -Wall               #REM: Enable almost all standard compiler warnings
    -Wextra             #REM: Enable even more hyper-strict optional warnings
    -Wconversion        #REM: Warn on numeric narrowing (e.g., storing size_t in an int)
    -Wfloat-conversion  #REM: Catch implicit float drops (e.g., fixes the 'int y = 1.1f;' silent bug)
    -Werror             #REM: STOP THE BUILD IMMEDIATELY if any warning occurs
  )
else()
  #REM: ------------------------------------------------------------
  #REM: MICROSOFT VISUAL C++ (MSVC toolchain)
  #REM: ------------------------------------------------------------
  target_compile_options(${PROJECT_NAME}_target_main_lib
    PRIVATE
    /permissive-        #REM: Force strict C++ standard compliance (disable MSVC loopholes)
    /W4                 #REM: Enable production-ready Warning Level 4 (highly recommended)
    /w14242             #REM: Warn on general data conversion loss
    /w14265             #REM: Warn if a class has virtual functions but lacks a virtual destructor
    /w14311             #REM: Warn on 64-bit pointer truncation (stops critical memory bugs)
    /WX                 #REM: STOP THE BUILD IMMEDIATELY if any warning occurs
  )
endif()

target_sources(${PROJECT_NAME}_target_main_lib
  PRIVATE
    ${learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_CXX_MAIN_SOURCES}
  
  #REM: [KEYPOINT] Private headers are internal implementation details
  PRIVATE FILE_SET private_header_main_sources
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/private
    #REM: Omitted FILES as intended
    # FILES
    #   ${learn_cpp.project_structure.cmake_3_23_way.CMAKE_PRIVATE_HEADER_MAIN_SOURCES}
      
  PUBLIC FILE_SET public_header_main_sources
    TYPE HEADERS
    BASE_DIRS 
      ${CMAKE_CURRENT_SOURCE_DIR}/public
      ${CMAKE_CURRENT_BINARY_DIR}/.generate/include
    FILES
      ${learn_cpp.project_structure.cmake_3_23_way.CMAKE_PUBLIC_HEADER_MAIN_SOURCES}
      ${CMAKE_CURRENT_BINARY_DIR}/.generate/include/cmake_3_23_way_export.h
)

include(GNUInstallDirs)

install(TARGETS
  ${PROJECT_NAME}_target_main_lib
  EXPORT ${PROJECT_NAME}_targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET public_header_main_sources DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}_targets
  NAMESPACE learn_cpp.project_structure::
  FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION} #REM: Uses the version defined in your project() call
  COMPATIBILITY SameMajorVersion #REM: Options: AnyNewerVersion, SameMajorVersion, ExactVersion
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")\n")

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
