cmake_minimum_required (VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 17)
message(STATUS "CMAKE_CXX_STANDARD " + ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD_REQUIRED " + ${CMAKE_CXX_STANDARD_REQUIRED})
set(CXX_EXTENSIONS OFF)
message(STATUS "CXX_EXTENSIONS " + ${CXX_EXTENSIONS})

project (GameEngine)

message(STATUS "CMAKE_SYSTEM_NAME " + ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_HOST_SYSTEM_NAME " + ${CMAKE_HOST_SYSTEM_NAME})
set(CMAKE_SYSTEM_VERSION latest)
message(STATUS "CMAKE_SYSTEM_VERSION " + ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
message(STATUS "CMAKE_SYSTEM_VERSION " + ${CMAKE_SYSTEM_VERSION})

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
else()
    message("-- CMAKE_BUILD_TYPE=" "${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "CMake Binary Dir " + ${CMAKE_BINARY_DIR})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#### ENGINE ###
add_library (engine STATIC  
                Hazel/src/Application.cpp 
                Hazel/src/Log.cpp
                Hazel/src/Platform/Windows/WindowsWindow.cpp
                Hazel/src/Layer.cpp
                Hazel/src/LayerStack.cpp
                Hazel/src/ImGui/ImGuiLayer.cpp
                Hazel/src/Platform/Windows/WindowsInput.cpp
                Hazel/src/ImGui/ImGuiBuild.cpp
                Hazel/src/Platform/OpenGL/OpenGLContext.cpp
                Hazel/src/Renderer/Shader.cpp
            )
find_package (OpenGL REQUIRED)
target_include_directories(engine PRIVATE Hazel)
target_link_libraries(engine PRIVATE ${CONAN_LIBS_FMT} ${CONAN_LIBS_SPDLOG} ${CONAN_LIBS_GLFW} ${CONAN_LIBS_GLAD} ${CONAN_LIBS_IMGUI} ${CONAN_LIBS_GLM} opengl32)
if (WIN32)
    target_compile_definitions(engine PRIVATE HZ_PLATFORM_WINDOWS)
    target_compile_definitions(engine PRIVATE HZ_BUILD_DLL)
    target_compile_definitions(engine PRIVATE GLFW_INCLUDE_NONE)#tell glfw to stop include opengl headers
endif (WIN32)
target_precompile_headers(engine PRIVATE Hazel/src/pch.h)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    #set_property(TARGET engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    #message("-- MSVC_RUNTIME_LIBRARY - engine = MultiThreadedDebug")
    target_compile_definitions(engine PRIVATE HZ_DEBUG)
else()
    #set_property(TARGET engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
    #message("-- MSVC_RUNTIME_LIBRARY - engine = MultiThreaded")
    target_compile_definitions(engine PRIVATE HZ_RELEASE)
endif()

#### SANDBOX APP ###
add_executable (sandbox Sandbox/src/SandboxApp.cpp)
target_include_directories(sandbox PRIVATE Hazel)
if (WIN32)
    target_compile_definitions(sandbox PRIVATE HZ_PLATFORM_WINDOWS)
endif (WIN32)
# if(CMAKE_BUILD_TYPE MATCHES Debug)
#     set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
#     message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreadedDebug")
# else()
#     set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
#     message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreaded")
# endif()

target_link_libraries(sandbox PRIVATE engine)