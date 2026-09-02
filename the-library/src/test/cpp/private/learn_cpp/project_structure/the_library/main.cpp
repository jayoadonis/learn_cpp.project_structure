#include <cstdio>

#include "learn_cpp/project_structure/the_library/func_i.h"

int main(int arg_c, char** arg_v) {

  using namespace learn_cpp::project_structure;

  the_library::func_i(1.1f);

  std::fprintf(stdout, "%s\n", "Hi there.");
  return 0;
}