export module learn_cpp.the_library_module:pkg_name.ClassB;

namespace learn_cpp::the_library_module::pkg_name {
  export template<typename T> class ClassB {
      public: explicit ClassB(T const x) : x{ x } {}
      public: virtual ~ClassB() = default;
      public: virtual T get_x() { 
        return this->x; 
      }
      private: T x;
  };
}