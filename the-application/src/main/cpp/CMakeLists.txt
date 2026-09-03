file(GLOB_RECURSE
  learn_cpp.project_structure.the_application.MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp)

add_executable(
  ${PROJECT_NAME}-app
  ${learn_cpp.project_structure.the_application.MAIN_SOURCES})
add_executable(
  learn_cpp::the_application
  ALIAS
  ${PROJECT_NAME}-app)
set_target_properties(
  ${PROJECT_NAME}-app
  PROPERTIES
  OUTPUT_NAME ${learn_cpp.project_structure.the_application.OUTPUT_NAME})
target_include_directories(
  ${PROJECT_NAME}-app
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/private
  # PUBLIC
  # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
  # $<INSTALL_INTERFACE:include>
)

message(STATUS ">>>> ${CMAKE_PREFIX_PATH}")

# list(APPEND CMAKE_PREFIX_PATH "${learn_cpp.project_structure.the_library.INSTALL_DIR}")
find_package(
  the-library_main_shared "0.1.0" REQUIRED)

# set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs" FORCE)
target_link_libraries(
  ${PROJECT_NAME}-app
  PRIVATE
  learn_cpp.project_structure::the-library_main_shared)

add_custom_command(
  TARGET 
  ${PROJECT_NAME}-app
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:learn_cpp.project_structure::the-library_main_shared>"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}-app>"
  COMMENT "::: Copying shared library to application build directory"
  VERBATIM)

install(
  TARGETS
    ${PROJECT_NAME}-app
    # learn_cpp.project_structure::the-library_main_shared
  EXPORT ${PROJECT_NAME}-targets
  # LIBRARY DESTINATION 
  #   ${learn_cpp.project_structure.the_application.INSTALL_INFIX_DIR}/lib
  # ARCHIVE DESTINATION  
  #   ${learn_cpp.project_structure.the_application.INSTALL_INFIX_DIR}/lib
  RUNTIME DESTINATION 
    ${learn_cpp.project_structure.the_application.INSTALL_INFIX_DIR}/bin
  COMPONENT application)