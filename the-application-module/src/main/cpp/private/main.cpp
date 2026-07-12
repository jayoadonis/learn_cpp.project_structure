
import learn_cpp.the_application_module;
import learn_cpp.the_library_module;

#include <cstdio>

int main(int arg_c, char** arg_v) {

  std::printf("%s\n", "Hi there!");

  float x = 
    learn_cpp::the_application_module::pkg_name::func_i(1.1);

  float y = 
    learn_cpp::the_library_module::pkg_name::func_i(1.0);

  std::printf("%.2f, %.2f\n====\n", x, y);

  float z =
    learn_cpp::the_application_module::pkg_name::func_i();

  std::printf(">>> %.2f\n", z);

  float w =
    learn_cpp::the_application_module::pkg_name::func_i_a();

  std::printf("<<< %.2f\n", w);
  return 0;
}