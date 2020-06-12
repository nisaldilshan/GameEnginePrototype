from conans import ConanFile, CMake

class OpenGLTest(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "spdlog/1.6.1", "glfw/3.2.1@bincrafters/stable"
   generators = "cmake"
   build_policy = "missing"

   def configure(self):
      if self.settings.compiler == "Visual Studio":
         if self.settings.build_type == "Debug":
            self.settings.compiler.runtime = "MDd"