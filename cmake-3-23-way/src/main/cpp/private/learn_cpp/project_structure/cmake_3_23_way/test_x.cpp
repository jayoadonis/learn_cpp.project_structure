
#include "learn_cpp/project_structure/cmake_3_23_way/test_x.h"

#include <cstdio>

namespace learn_cpp::project_structure::cmake_3_23_way {

  void test_x(float x) {

    std::fprintf(stdout, 
      "::: %.2f\n", (1.0f*x));
  }
}