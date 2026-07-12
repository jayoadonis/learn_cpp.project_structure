//REM: func_i
export module learn_cpp.the_application_module:pkg_name.func_i;

import learn_cpp.the_library_module;

namespace learn_cpp::the_application_module::pkg_name {

  export float func_i(float x) {

    return x * 2;
  }

  export float func_i() {
    
    learn_cpp::the_library_module::pkg_name::ClassA cA(0.1f);

    return cA.get_x();
  }

  export float func_i_a() {
    
    learn_cpp::the_library_module::pkg_name::ClassB<float> cA(1.11f);

    return cA.get_x();
  }
}

