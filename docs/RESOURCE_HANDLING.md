# Resource handling
OS | static (not-embedded, read-only) | dynamic (read/write) | static (embedded)
---|---|---|---
Windows | C:/program files/{project_name}/resources | C:/users/{name}/appdata/roaming/{project_name}/resources | ---
Linux | /usr/share/{project_name}/resources | ~/.local/share/{project_name}/resources | ---
Apple | {project_name}.app/contents/resources| ~/library/application/support/{project_name}/resources | ---

---

## Cross-Platform C++17 Runtime Path Resolution Code
```cpp
#include <iostream>
#include <filesystem>
#include <cstdlib> //REM: For std::getenv
#include <string>

//REM: Platform-specific headers required to safely resolve the binary path
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN //REM: Don't include bloated unused legacy
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <limits.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

namespace fs = std::filesystem;

//REM: ============================================================================
//REM: 1. PINPOINT THE ABSOLUTE LOCATION OF THE RUNNING EXECUTABLE BINARY
//REM: ============================================================================
fs::path get_executable_directory() {
#if defined(_WIN32)
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return fs::path(path).parent_path();
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        //REM: Resolve symlinks to prevent relative breakout loops
        return fs::canonical(fs::path(path)).parent_path();
    }
    return fs::current_path();
#elif defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count > 0) {
        return fs::canonical(fs::path(std::string(result, count))).parent_path();
    }
    return fs::current_path();
#else
    return fs::current_path(); //REM: Fallback for unsupported systems
#endif
}

//REM: ============================================================================
//REM: 2. GET THE READ-ONLY STATIC RESOURCE BUNDLE PATH (CPack Installation Paths)
//REM: ============================================================================
fs::path get_static_assets_path(const std::string& project_name) {
    fs::path bin_dir = get_executable_directory();
#if defined(_WIN32)
    //REM: Windows Portable Layout: assets sit side-by-side next to the executable
    return bin_dir / "assets";
#elif defined(__APPLE__)
    //REM: macOS App Bundle Layout: navigate inside the app bundle contents wrapper
    return bin_dir.parent_path() / "Resources" / "assets";
#else
    //REM: Linux FHS Layout: escape out of 'bin/' and drop down into 'share/project/'
    return bin_dir.parent_path() / "share" / project_name / "assets";
#endif
}

//REM: ============================================================================
//REM: 3. GET OR CREATE THE PERMANENT WRITABLE DATA PATH (Saves, Configs, Logs)
//REM: ============================================================================
fs::path get_writable_runtime_path(const std::string& project_name) {
    fs::path target_path;
#if defined(_WIN32)
    const char* appdata = std::getenv("APPDATA");
    if (appdata) {
        target_path = fs::path(appdata) / project_name;
    } else {
        const char* userprofile = std::getenv("USERPROFILE");
        if (userprofile) {
            target_path = fs::path(userprofile) / "AppData" / "Roaming" / project_name;
        } else {
            target_path = fs::current_path() / "appdata" / project_name;
        }
    }
#elif defined(__APPLE__)
    const char* home = std::getenv("HOME");
    if (home) {
        target_path = fs::path(home) / "Library" / "Application Support" / project_name;
    } else {
        target_path = fs::current_path() / "appdata" / project_name;
    }
#else
    const char* xdg_data = std::getenv("XDG_DATA_HOME");
    if (xdg_data) {
        target_path = fs::path(xdg_data) / project_name;
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            target_path = fs::path(home) / ".local" / "share" / project_name;
        } else {
            target_path = fs::current_path() / "appdata" / project_name;
        }
    }
#endif

    //REM: Physically guarantee the destination exists on disk immediately
    fs::create_directories(target_path);
    return target_path;
}

//REM: ============================================================================
//REM: 4. GET OR CREATE THE DYNAMIC TEMPORARY WRITABLE PATH (Volatile Cache/Tmp)
//REM: ============================================================================
fs::path get_temporary_resource_path(const std::string& project_name) {
    fs::path target_path;
#if defined(_WIN32)
    const char* win_temp = std::getenv("TEMP");
    const char* win_tmp  = std::getenv("TMP");
    const char* local_app = std::getenv("LOCALAPPDATA");

    if (win_temp) {
        target_path = fs::path(win_temp) / project_name / "resources";
    } else if (win_tmp) {
        target_path = fs::path(win_tmp) / project_name / "resources";
    } else if (local_app) {
        target_path = fs::path(local_app) / "Temp" / project_name / "resources";
    }
#elif defined(__APPLE__)
    const char* mac_tmp = std::getenv("TMPDIR");
    if (mac_tmp) {
        target_path = fs::path(mac_tmp) / project_name / "resources";
    }
#else
    const char* linux_tmp = std::getenv("TMPDIR");
    if (linux_tmp) {
        target_path = fs::path(linux_tmp) / project_name / "resources";
    }
#endif

    //REM: Core Fallback Check: Use standard C++17 library helper if variables are blocked/empty
    try {
        if (target_path.empty()) {
            target_path = fs::temp_directory_path() / project_name / "resources";
        }
    } catch (...) {
        //REM: Ultimate fallback to isolated working folder path execution context
        target_path = fs::current_path() / "tmp" / project_name / "resources";
    }

    fs::create_directories(target_path);
    return target_path;
}

//REM: ============================================================================
//REM: 5. APPLICATION RUNTIME EXECUTION PROOF
//REM: ============================================================================
int main() {
    const std::string app_name = "MyModularProject";

    //REM: 1. Resolve Path Targets
    fs::path binary_dir    = get_executable_directory();
    fs::path static_assets = get_static_assets_path(app_name);
    fs::path permanent_dir = get_writable_runtime_path(app_name);
    fs::path temporary_dir = get_temporary_resource_path(app_name);

    //REM: 2. Output Platform Mappings
    std::cout << "--- CROSS-PLATFORM PATHS MANAGEMENT ENGINE (C++17) ---" << std::endl;
    std::cout << "[BINARY EXECUTABLE]  " << binary_dir.string()    << std::endl;
    std::cout << "[READ-ONLY ASSETS]   " << static_assets.string()  << std::endl;
    std::cout << "[PERSISTENT WRITE]   " << permanent_dir.string()  << std::endl;
    std::cout << "[VOLATILE TEMP CACHE] " << temporary_dir.string()  << std::endl;

    return 0;
}
```

---

## Cross-Platform C++20 Runtime Path Resolution Code
```cpp
//REM: BEGIN: SystemPaths.cppm (primary module interface)
export module system.paths;

import <filesystem>;
import <string>;

export namespace sys::paths {
    [[nodiscard]] std::filesystem::path get_executable_directory();
    [[nodiscard]] std::filesystem::path get_static_assets_path(const std::string& project_name);
    [[nodiscard]] std::filesystem::path get_writable_runtime_path(const std::string& project_name);
    [[nodiscard]] std::filesystem::path get_temporary_resource_path(const std::string& project_name);
}
//REM: END: SystemPaths.cppm (primary module interface)

//REM: BEGIN: SystemPaths.cpp (module implementation)
module system.paths;

import <filesystem>;
import <cstdlib>;
import <string>;

//REM: Platform system bindings (must remain localized inside implementation scopes)
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN //REM: Don't include bloated unused legacy
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <limits.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#endif

namespace fs = std::filesystem;

namespace sys::paths {

//REM: 1. PINPOINT THE ABSOLUTE LOCATION OF THE RUNNING EXECUTABLE BINARY
fs::path get_executable_directory() {
#if defined(_WIN32)
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return fs::path(path).parent_path();
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        return fs::canonical(fs::path(path)).parent_path();
    }
    return fs::current_path();
#elif defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count > 0) {
        return fs::canonical(fs::path(std::string(result, count))).parent_path();
    }
    return fs::current_path();
#else
    return fs::current_path();
#endif
}

//REM: 2. GET THE READ-ONLY STATIC RESOURCE BUNDLE PATH
fs::path get_static_assets_path(const std::string& project_name) {
    fs::path bin_dir = get_executable_directory();
#if defined(_WIN32)
    return bin_dir / "assets";
#elif defined(__APPLE__)
    return bin_dir.parent_path() / "Resources" / "assets";
#else
    return bin_dir.parent_path() / "share" / project_name / "assets";
#endif
}

//REM: 3. GET OR CREATE THE PERMANENT WRITABLE DATA PATH
fs::path get_writable_runtime_path(const std::string& project_name) {
    fs::path target_path;
#if defined(_WIN32)
    if (const char* appdata = std::getenv("APPDATA")) {
        target_path = fs::path(appdata) / project_name;
    } else if (const char* userprofile = std::getenv("USERPROFILE")) {
        target_path = fs::path(userprofile) / "AppData" / "Roaming" / project_name;
    } else {
        target_path = fs::current_path() / "appdata" / project_name;
    }
#elif defined(__APPLE__)
    if (const char* home = std::getenv("HOME")) {
        target_path = fs::path(home) / "Library" / "Application Support" / project_name;
    } else {
        target_path = fs::current_path() / "appdata" / project_name;
    }
#else
    if (const char* xdg_data = std::getenv("XDG_DATA_HOME")) {
        target_path = fs::path(xdg_data) / project_name;
    } else if (const char* home = std::getenv("HOME")) {
        target_path = fs::path(home) / ".local" / "share" / project_name;
    } else {
        target_path = fs::current_path() / "appdata" / project_name;
    }
#endif

    fs::create_directories(target_path);
    return target_path;
}

//REM: 4. GET OR CREATE THE DYNAMIC TEMPORARY WRITABLE PATH
fs::path get_temporary_resource_path(const std::string& project_name) {
    fs::path target_path;
#if defined(_WIN32)
    const char* win_temp = std::getenv("TEMP");
    const char* win_tmp  = std::getenv("TMP");
    const char* local_app = std::getenv("LOCALAPPDATA");

    if (win_temp)       target_path = fs::path(win_temp) / project_name / "resources";
    else if (win_tmp)   target_path = fs::path(win_tmp) / project_name / "resources";
    else if (local_app) target_path = fs::path(local_app) / "Temp" / project_name / "resources";
#elif defined(__APPLE__)
    if (const char* mac_tmp = std::getenv("TMPDIR")) {
        target_path = fs::path(mac_tmp) / project_name / "resources";
    }
#else
    if (const char* linux_tmp = std::getenv("TMPDIR")) {
        target_path = fs::path(linux_tmp) / project_name / "resources";
    }
#endif

    try {
        if (target_path.empty()) {
            target_path = fs::temp_directory_path() / project_name / "resources";
        }
    } catch (...) {
        target_path = fs::current_path() / "tmp" / project_name / "resources";
    }

    fs::create_directories(target_path);
    return target_path;
}

} //REM: namespace sys::paths
//REM: END:  SystemPaths.cpp (module implementation)

//REM: BEGIN: main.cpp
import system.paths; //REM: Pulls in our C++20 paths engine

import <iostream>;
import <filesystem>;
import <fstream>;
import <string>;

namespace fs = std::filesystem;

void bootstrap_resources(const std::string& app_name) {
    
    std::filesystem::path binary_dir    = sys::paths::get_executable_directory();

    //REM: 1. Resolve our exact cross-platform location paths
    fs::path static_assets_dir = sys::paths::get_static_assets_path(app_name);
    fs::path permanent_data_dir = sys::paths::get_writable_runtime_path(app_name);
    fs::path temporary_cache_dir = sys::paths::get_temporary_resource_path(app_name);
    

    std::cout << "--- C++20 MODULAR PATHS SYSTEM INTERFACE ---" << std::endl;
    std::cout << "[BINARY LOCATION] " << binary_dir.string()    << std::endl;
    std::cout << "[STATIC ASSETS]   " << static_assets_dir.string()  << std::endl;
    std::cout << "[WRITE REPOSITORY]" << permanent_data_dir.string()  << std::endl;
    std::cout << "[VOLATILE TEMP]   " << temporary_cache_dir.string()  << std::endl;

    //REM: 2. Map out our expected individual resource files
    fs::path master_template   = static_assets_dir  / "config_template.json"; //REM: Read-only master
    fs::path user_settings     = permanent_data_dir / "user_settings.json";    //REM: Persistent file
    fs::path active_log        = permanent_data_dir / "app.log";               //REM: Persistent log
    fs::path session_buffer    = temporary_cache_dir / "session.tmp";          //REM: Volatile temp file

    std::cout << "--- BOOTSTRAPPING FILESYSTEM RESOURCES ---\n" << std::endl;

    try {
        //REM: ====================================================================
        //REM: A. HANDLE READ-ONLY MASTER ASSETS
        //REM: ====================================================================
        if (!fs::exists(master_template)) {
            std::cerr << "[CRITICAL ERROR] Master template file is missing from installation bounds: " 
                      << master_template.string() << "\nCheck your CPack distribution package installer!\n" << std::endl;
            //REM: (In a real application, you might want to throw an exception or exit here)
        } else {
            std::cout << "[READ-ONLY FIXED ASSET] Found master template package file at: " 
                      << master_template.string() << std::endl;
        }

        //REM: ====================================================================
        //REM: B. HANDLE PERSISTENT WRITABLE RESOURCES (User settings / profiles)
        //REM: ====================================================================
        //REM: Remember: sys::paths::get_writable_runtime_path already called fs::create_directories
        if (!fs::exists(user_settings)) {
            std::cout << "[PERSISTENT WRITE] First-time setup detected. Initializing user configuration..." << std::endl;
            
            if (fs::exists(master_template)) {
                //REM: Securely copy the template asset over to the user data folder so they can mutate it
                fs::copy_file(master_template, user_settings, fs::copy_options::overwrite_existing);
                std::cout << "[PERSISTENT WRITE] Created live copy from installation template." << std::endl;
            } else {
                //REM: Resilient Fallback: If the master installer template is broken, construct a basic JSON file manually
                std::ofstream fallback_file(user_settings);
                fallback_file << "{\n  \"first_launch\": true,\n  \"user_theme\": \"dark\"\n}\n";
                fallback_file.close();
                std::cout << "[PERSISTENT WRITE] Created local raw fallback JSON template." << std::endl;
            }
        }

        //REM: Append active status to our log resource file
        std::ofstream log_stream(active_log, std::ios::app);
        if (log_stream.is_open()) {
            log_stream << "[INFO] Application booted up and resource paths securely mounted.\n";
            log_stream.close();
            std::cout << "[PERSISTENT WRITE] Appended session marker to log resource file: " << active_log.string() << std::endl;
        }

        //REM: ====================================================================
        //REM: C. HANDLE VOLATILE TEMPORARY RESOURCES
        //REM: ====================================================================
        //REM: sys::paths::get_temporary_resource_path already initialized this directory tree
        std::ofstream temp_stream(session_buffer);
        if (temp_stream.is_open()) {
            temp_stream << "ACTIVE_PID_SESSION_STREAM_DATA_CACHE_BUFFER\n";
            temp_stream.close();
            std::cout << "[VOLATILE TMP CACHE] Spawned runtime volatile session cache at: " << session_buffer.string() << std::endl;
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "[FILESYSTEM ERROR] Failed to mount runtime system profiles: " << e.what() << std::endl;
    }
}

int main() {
    const std::string app_name = "MyModularProject";
    bootstrap_resources(app_name);
    return 0;
}
//REM: END: main.cpp
```
---

## Bonus Cmake target sources c++20 module
```cmake
target_sources(my_app
    PRIVATE
        main.cpp
    PRIVATE FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
        SystemPaths.cppm   #REM: Interface file goes here
    PRIVATE
        SystemPaths.cpp    #REM: Implementation file goes here
)
```