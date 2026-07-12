
module learn_cpp.the_library_module;

namespace learn_cpp::the_library_module::pkg_name {

  ClassA::ClassA(float const x) {
    this->x = x;
  }

  ClassA::~ClassA() {

  }

  float ClassA::get_x() {
    return this->x;
  }
}