```bash
project_structure/
|---  CMakeLists.txt
|---  build/
|---  the-library/
|     |---  CMakeLists.txt
|     |---  cmake/
|     |     |---  sync_res_incremental.cmake
|     |     \---  .generate/
|     \---  src/
|           |---  main/
|           |     |---  cpp/
|           |     |     |---  CMakeLists.txt
|           |     |     |---  private/*.{cpp,h}
|           |     |     \---  public/*.h
|           |     \---  resources/
|           \---  test/
|                 |---  cpp/
|                 |     |---  CMakeLists.txt
|                 |     \---  private/*.{cpp,h}
|                 \---  resources/
\---  the-application/
      |---  CMakeLists.txt
      |---  cmake/
      |     |---  sync_res_incremental.cmake
      |     \---  .generate/
      \---  src/
            |---  main/
            |     |---  cpp/
            |     |     |---  CMakeLists.txt
            |     |     \---  private/*.{cpp,h}
            |     \---  resources/
            \---  test/
                  |---  cpp/
                  |     |---  CMakeLists.txt
                  |     \---  private/*.{cpp,h}
                  \---  resources/
```
> IMPORTANT: Observe the OS max path limit it may exceeds, 
> `e.g. IN WINDOWS-OS: By default/legacy the fully qualified file name must be less than 260 characters.`
> There are fixes, however not portable.

---

```bash
#REM: Single-Config Generator
cmake -S . -B build[/<generator_name>[_<arch>]] -G "<single_config_generator_name>" [-DCMAKE_BUILD_TYPE=(debug|release)]
cmake --build build[/<generator_name>[_<arch>]] [--clean-first]

#REM: Multi-Config Generator
cmake -S . -B build[/<generator_name>[_<arch>]] -G "<multi_config_generator_name>"
cmake --build build[/<generator_name>[_<arch>]] [--config (debug|release)] [--clean-first]

#REM: Test
ctest --test-dir build[/<generator_name>[_<arch>]][/<project_name>] [-R "match test name"] [-L "match test label name"] [-VV] [-C (debug|release)] 

#REM: Install, usually by default config is 'release'
cmake --install build[/<generator_name>[_<arch>]] [--prefix <path/to/install>] [--config (debug|release)] 

#REM: Note, at config phase we can add `-DBUILD_TESTING=(ON|OFF)`
```


```bash
#REM: CPack
cpack --config build[/<generator_name>[_<arch>]]/CPackConfig.cmake [-C (debug|release)] [-B install/container] [-VV]
```

---

## Resource handling
OS | static (not-embedded) | dynamic (runtime) | static (embedded)
---|---|---|---
Windows | C:/program files/{project_name}/resources | C:/users/{name}/appdata/roaming/{project_name}/resources | ---
Linux | /usr/share/{project_name}/resources | ~/.local/share/{project_name}/resources | ---
Apple | {project_name}.app/contents/resources| ~/library/application/support/{project_name}/resources | ---
