cmake_minimum_required (VERSION 3.16.0)
project (Engine)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library (engine SHARED 
                Hazel/src/Application.cpp 
                Hazel/src/Log.cpp
                Hazel/src/Platform/Windows/WindowsWindow.cpp
            )
find_package (OpenGL REQUIRED)
target_link_libraries(engine ${CONAN_LIBS_FMT} ${CONAN_LIBS_SPDLOG} ${CONAN_LIBS_GLFW} opengl32)
if (WIN32)
    target_compile_definitions(engine PRIVATE HZ_PLATFORM_WINDOWS)
    target_compile_definitions(engine PRIVATE HZ_BUILD_DLL)
endif (WIN32)
target_precompile_headers(engine PRIVATE Hazel/src/pch.h)


add_executable (sandbox Sandbox/src/SandboxApp.cpp)
target_include_directories(sandbox PUBLIC Hazel)
target_link_libraries(sandbox engine)
if (WIN32)
    target_compile_definitions(sandbox PRIVATE HZ_PLATFORM_WINDOWS)
endif (WIN32)