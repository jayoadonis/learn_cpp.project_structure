
#include <cstdio>
#include "learn_cpp/project_structure/the_library/func_i.h"

namespace learn_cpp::project_structure::the_library {

  void func_i(float x) {
    std::printf("::: %s, %.2f\n", "Hi there", x);
  }
}