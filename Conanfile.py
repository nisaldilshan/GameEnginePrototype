from conans import ConanFile, CMake

class OpenGLTest(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "spdlog/1.6.1"
   generators = "cmake"