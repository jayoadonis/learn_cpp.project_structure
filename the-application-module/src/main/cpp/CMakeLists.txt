file(GLOB_RECURSE
  learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.ixx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cppm)

# file(GLOB_RECURSE
#   learn_cpp.the_application_module.CMAKE_PUBLIC_CPP_MAIN_SOURCES
#   CONFIGURE_DEPENDS
#   ${CMAKE_CURRENT_SOURCE_DIR}/public/*.cppm
#   ${CMAKE_CURRENT_SOURCE_DIR}/public/*.ixx)

set(learn_cpp.the_application_module.CMAKE_MAIN_ENTRY
  ${learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_SOURCES})
  
set(learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_MODULES
  ${learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_SOURCES})
  
# set(learn_cpp.the_application_module.CMAKE_PUBLIC_CPP_MAIN_MODULES
#   ${learn_cpp.the_application_module.CMAKE_PUBLIC_CPP_MAIN_SOURCES})
  
list(FILTER
  learn_cpp.the_application_module.CMAKE_MAIN_ENTRY
  INCLUDE REGEX "main\\.cpp$")
  
list(FILTER
  learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_MODULES
  EXCLUDE REGEX "main\\.cpp$")

# find_package(the-library-module "0.1.0" REQUIRED)
add_executable(${PROJECT_NAME}-target-main-app)
target_sources(${PROJECT_NAME}-target-main-app
  PRIVATE
  ${learn_cpp.the_application_module.CMAKE_MAIN_ENTRY}
  PRIVATE
  FILE_SET CXX_MODULES
  FILES ${learn_cpp.the_application_module.CMAKE_PRIVATE_CPP_MAIN_MODULES})
set_target_properties(
  ${PROJECT_NAME}-target-main-app
  PROPERTIES
  OUTPUT_NAME
  ${learn_cpp.the_application_module.CMAKE_GENEXP_OUTPUT_NAME})
#REM: usually don't need this at C++20 modularization
# target_include_directories(
#   ${PROJECT_NAME}-target-main-app
#   PRIVATE
#   ${CMAKE_CURRENT_SOURCE_DIR}/private
#   PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
#   $<INSTALL_INTERFACE:${learn_cpp.the_application_module.CMAKE_INSTALL_INFIX_DIR}/include>)
target_link_libraries(
  ${PROJECT_NAME}-target-main-app
  PRIVATE
  learn_cpp::the-library-module)

install(
  TARGETS
  ${PROJECT_NAME}-target-main-app
  # EXPORT ${PROJECT_NAME}-target
  RUNTIME DESTINATION
    ${learn_cpp.the_application_module.CMAKE_INSTALL_INFIX_DIR}/bin
    COMPONENT application
  FILE_SET CXX_MODULES DESTINATION 
  ${learn_cpp.the_application_module.CMAKE_INSTALL_INFIX_DIR}/lib/modules/bmi
    COMPONENT application)

# set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
# set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
# set(CPACK_GENERATOR "ZIP;TGZ")
# set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
# set(CPACK_COMPONENT_NO_NAME ON)
# set(CPACK_COMPONENTS_ALL "application")
# set(CPACK_ARCHIVE_APPLICATION_FILE_NAME 
#   "${PROJECT_NAME}-${PROJECT_VERSION}-app")
# set(CPACK_ARCHIVE_LIBRARY_FILE_NAME 
#   "${PROJECT_NAME}-${PROJECT_VERSION}-lib")
# include(CPack)