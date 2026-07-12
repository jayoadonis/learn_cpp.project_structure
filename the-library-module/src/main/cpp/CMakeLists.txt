file(GLOB_RECURSE
  learn_cpp.the_library_module.CMAKE_PRIVATE_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.ixx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cppm)

file(GLOB_RECURSE
  learn_cpp.the_library_module.CMAKE_PUBLIC_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.ixx
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.cppm)

add_library(${PROJECT_NAME}_target_main_lib STATIC)
add_library(learn_cpp::${PROJECT_NAME}
  ALIAS ${PROJECT_NAME}_target_main_lib)

target_sources(${PROJECT_NAME}_target_main_lib
  PRIVATE FILE_SET private_file_set_cxx_modules TYPE CXX_MODULES
    FILES ${learn_cpp.the_library_module.CMAKE_PRIVATE_CXX_MAIN_SOURCES}
  PUBLIC FILE_SET public_file_set_cxx_modules TYPE CXX_MODULES
    FILES ${learn_cpp.the_library_module.CMAKE_PUBLIC_CXX_MAIN_SOURCES})

set_target_properties(${PROJECT_NAME}_target_main_lib
  PROPERTIES
  OUTPUT_NAME ${learn_cpp.the_library_module.CMAKE_GENEXP_OUTPUT_NAME})

install(
  TARGETS ${PROJECT_NAME}_target_main_lib

  LIBRARY DESTINATION ${learn_cpp.the_library_module.CMAKE_INSTALL_INFIX_DIR}/lib
  COMPONENT ${PROJECT_NAME}_component_main_lib
  
  ARCHIVE DESTINATION ${learn_cpp.the_library_module.CMAKE_INSTALL_INFIX_DIR}/lib
  COMPONENT ${PROJECT_NAME}_component_main_lib

  RUNTIME DESTINATION ${learn_cpp.the_library_module.CMAKE_INSTALL_INFIX_DIR}/bin
  COMPONENT ${PROJECT_NAME}_component_main_lib

  FILE_SET public_file_set_cxx_modules
    DESTINATION ${learn_cpp.the_library_module.CMAKE_INSTALL_INFIX_DIR}/lib/modules/bmi)