
export module learn_cpp.the_library_module:pkg_name.ClassA;

namespace learn_cpp::the_library_module::pkg_name {

  export class ClassA {
    public: explicit ClassA(float const x);
    public: virtual ~ClassA();

    public: virtual float get_x();

    private: float x = 0.0f;
  };
}