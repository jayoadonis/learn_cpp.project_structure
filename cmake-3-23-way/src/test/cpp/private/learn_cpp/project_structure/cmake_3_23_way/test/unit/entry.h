#ifndef LEARN_CPP_PROJECT_STRUCTURE_CMAKE_3_23_WAY_TEST_UNIT_ENTRY_H
#define LEARN_CPP_PROJECT_STRUCTURE_CMAKE_3_23_WAY_TEST_UNIT_ENTRY_H

#include <cassert>
#include "learn_cpp/project_structure/cmake_3_23_way/test_x.h"

namespace learn_cpp::project_structure::cmake_3_23_way::test::unit {

  void entry(int arg_c, char ** arg_v) {

    using namespace learn_cpp::project_structure;

    cmake_3_23_way::test_x(3.14f); 
  }
}

#endif