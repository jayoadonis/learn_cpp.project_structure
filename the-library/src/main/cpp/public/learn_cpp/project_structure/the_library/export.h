#ifndef LCXX_PS_THELIBRARY_EXPORT_H
#define LCXX_PS_THELIBRARY_EXPORT_H

#if defined(LCXX_PS_THELIBRARY_BUILD_STATIC)
  //REM: Static linking, no decoration needed.
# define LCXX_PS_THELIBRARY_API
# define LCXX_PS_THELIBRARY_API_INTERNAL
#elif defined(LCXX_PS_THELIBRARY_BUILD_SHARED)
# if defined(_WIN32)
    //REM: Windows: export symbols from the DLL.
#   define LCXX_PS_THELIBRARY_API __declspec(dllexport)
#   define LCXX_PS_THELIBRARY_API_INTERNAL
# else
    //REM: Non‑Windows: apply visibility to counter -fvisibility=hidden.
#   if defined(__has_attribute) && __has_attribute(visibility)
#     define LCXX_PS_THELIBRARY_API __attribute__((visibility("default")))
#     define LCXX_PS_THELIBRARY_API_INTERNAL __attribute__((visibility("hidden")))
#   else
#     define LCXX_PS_THELIBRARY_API
#     define LCXX_PS_THELIBRARY_API_INTERNAL
#   endif
# endif
#else
  //REM: Consuming a shared library.
# if defined(_WIN32)
    //REM: Windows: import symbols from a DLL.
#   define LCXX_PS_THELIBRARY_API __declspec(dllimport)
#   define LCXX_PS_THELIBRARY_API_INTERNAL
# else
    //REM: Unix-like
#   define LCXX_PS_THELIBRARY_API
#   define LCXX_PS_THELIBRARY_API_INTERNAL
# endif
#endif //REM: defined(LCXX_PS_THELIBRARY_BUILD_STATIC)

//REM: Deprecation Macros
#if defined(__has_cpp_attribute) && __has_cpp_attribute(deprecated)
# define LCXX_PS_THELIBRARY_API_DEPRECATED [[deprecated]]
# define LCXX_PS_THELIBRARY_API_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#else
# if defined(_WIN32) 
#   define LCXX_PS_THELIBRARY_API_DEPRECATED __declspec(deprecated)
#   define LCXX_PS_THELIBRARY_API_DEPRECATED_MSG(msg) __declspec(deprecated(msg))
# elif defined(__has_attribute) && __has_attribute(deprecated)
#   define LCXX_PS_THELIBRARY_API_DEPRECATED __attribute__((deprecated))
#   define LCXX_PS_THELIBRARY_API_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
# else
#   define LCXX_PS_THELIBRARY_API_DEPRECATED
#   define LCXX_PS_THELIBRARY_API_DEPRECATED_MSG(msg)
# endif
#endif

#endif //REM: LCXX_PS_THELIBRARY_EXPORT_H
