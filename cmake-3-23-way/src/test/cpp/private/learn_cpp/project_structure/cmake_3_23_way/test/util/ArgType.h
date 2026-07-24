#ifndef LEARN_CPP_PROJECT_STRUCTURE_CMAKE_3_23_WAY_TEST_UTIL_ARG_TYPE_H
#define LEARN_CPP_PROJECT_STRUCTURE_CMAKE_3_23_WAY_TEST_UTIL_ARG_TYPE_H

#include <string_view>

namespace learn_cpp::project_structure::cmake_3_23_way::test::util {

  enum class ArgType {

    UNKNOWN = 0,
    UNIT,
    INTEGRATION
  };

  ArgType parse_to_arg_type(std::string_view const & sv) {

    if(sv == "unit") return ArgType::UNIT;
    if(sv == "integration") return ArgType::INTEGRATION;

    return ArgType::UNKNOWN;
  }
}

#endif