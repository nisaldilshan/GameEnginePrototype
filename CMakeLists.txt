cmake_minimum_required (VERSION 3.16.0)
project (Engine)


if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
else()
    message("-- CMAKE_BUILD_TYPE=" "${CMAKE_BUILD_TYPE}")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library (engine SHARED 
                Hazel/src/Application.cpp 
                Hazel/src/Log.cpp
                Hazel/src/Platform/Windows/WindowsWindow.cpp
                Hazel/src/Layer.cpp
                Hazel/src/LayerStack.cpp
            )
find_package (OpenGL REQUIRED)
target_link_libraries(engine ${CONAN_LIBS_FMT} ${CONAN_LIBS_SPDLOG} ${CONAN_LIBS_GLFW} opengl32)
if (WIN32)
    target_compile_definitions(engine PRIVATE HZ_PLATFORM_WINDOWS)
    target_compile_definitions(engine PRIVATE HZ_BUILD_DLL)
endif (WIN32)
target_precompile_headers(engine PRIVATE Hazel/src/pch.h)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_property(TARGET engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    message("-- MSVC_RUNTIME_LIBRARY = MultiThreadedDebugDLL")
endif()

add_executable (sandbox Sandbox/src/SandboxApp.cpp)
target_include_directories(sandbox PUBLIC Hazel)
target_link_libraries(sandbox engine)
if (WIN32)
    target_compile_definitions(sandbox PRIVATE HZ_PLATFORM_WINDOWS)
endif (WIN32)