from conans import ConanFile, CMake

class OpenGLTest(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "spdlog/1.6.1", "glfw/3.2.1@bincrafters/stable", "glad/0.1.33"
   generators = "cmake"
   build_policy = "missing"
   default_options = {
      "glad:no_loader":False,
      "glad:spec": "gl",
      "glad:extensions": "",
      "glad:gl_profile": "core",
      "glad:gl_version": 4.6
      } 

   def configure(self):
      if self.settings.compiler == "Visual Studio":
         if self.settings.build_type == "Debug":
            self.settings.compiler.runtime = "MDd"