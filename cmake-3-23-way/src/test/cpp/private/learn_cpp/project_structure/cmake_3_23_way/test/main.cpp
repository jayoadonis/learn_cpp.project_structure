#include <string>
#include <iostream>
#include <string_view>
#include <stdexcept>
#include <cstdio>

#include "learn_cpp/project_structure/cmake_3_23_way/test/unit/entry.h"
#include "learn_cpp/project_structure/cmake_3_23_way/test/util/ArgType.h"

int main(int arg_c, char ** arg_v) {

  using namespace learn_cpp::project_structure;

  try {

    if(arg_c < 2) 
      throw std::invalid_argument("Invalid argument, try either 'unit' or 'integration'");

    switch(std::string_view option = arg_v[1];
      cmake_3_23_way::test::util::parse_to_arg_type(option)
    ) {

      case cmake_3_23_way::test::util::ArgType::UNIT:
        cmake_3_23_way::test::unit::entry(arg_c, arg_v);
        break;

      case cmake_3_23_way::test::util::ArgType::INTEGRATION:
        throw std::logic_error("Integration testing not yet implemented");
        break;

      case cmake_3_23_way::test::util::ArgType::UNKNOWN:
        [[fallthrough]];
      default:
        throw std::invalid_argument("Invalid argument: " + std::string(option));
    }

  }
  catch(std::exception const & except) {
    std::fprintf(stderr, "Fatal Error: %s\n", except.what());
    return 1;
  }
  catch(...) {
    std::fprintf(stderr, "Fatal Error: Something went wrong.\n");
    return 1;
  }
  
  std::fprintf(stdout, "%s\n", "Done Testing.");
  return 0;
}