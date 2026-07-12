#ifndef LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC_SHARED_API_H
#define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC_SHARED_API_H

//REM: -------------------------------------------------------------------
//REM: Usage:
//REM:   - When *building* the library (any type, shared or static):
//REM:         define  LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_BUILD
//REM:   - When *consuming* the library as a shared library:
//REM:         do not define anything.
//REM:   - When linking statically and you want to *completely suppress*
//REM:     any export/import decoration (especially on Windows):
//REM:         define  LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC
//REM: 
//REM:   The macros LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_BUILD and LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC are mutually exclusive;
//REM:   if both are defined, LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC takes precedence.
//REM: -------------------------------------------------------------------

#if defined(LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_STATIC)
  //REM: Static linking, no decoration needed.
  #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API

#elif defined(LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_BUILD)
  //REM: Building the library (shared or static).
  //REM: We apply the correct export attribute so symbols are visible.
  #if defined(_WIN32) || defined(__CYGWIN__)
    //REM: Windows: export symbols from the DLL (harmless for static libs).
    #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API __declspec(dllexport)
  #else
    //REM: Non‑Windows: apply visibility to counter -fvisibility=hidden.
    #if defined(__has_attribute) && __has_attribute(visibility)
      #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API __attribute__((visibility("default")))
    #else
      #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API
    #endif
  #endif

#else
  //REM: Consuming a shared library.
  #if defined(_WIN32) || defined(__CYGWIN__)
    //REM: Windows: import symbols from a DLL.
    #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API __declspec(dllimport)
  #else
    //REM: Non‑Windows: nothing needed for consumers.
    #define LEARN_CPP_PROJECT_STRUCTURE_THE_LIBRARY_API
  #endif

#endif

#endif