from conans import ConanFile, CMake

class OpenGLTest(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "spdlog/1.6.1", "glfw/3.2.1@bincrafters/stable"
   generators = "cmake"