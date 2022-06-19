from conans import ConanFile, CMake


class OpenGLTest(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = ("spdlog/1.6.1", "glfw/3.3.2", "glad/0.1.33", "glm/0.9.9.8", "stb/20200203", "entt/3.7.1",
                "imgui/latest@nisaldilshan/docking", "yaml-cpp/0.7.0", "imguizmo/latest@nisaldilshan/latest",
                "shaderc/2021.1", "spirv-cross/cci.20211113", "box2d/2.4.1")
    generators = "cmake"
    build_policy = "missing"
    default_options = {
        "glad:no_loader": False,
        "glad:spec": "gl",
        "glad:extensions": "",
        "glad:gl_profile": "core",
        "glad:gl_version": 4.6
    }

    def requirements(self):
        if self.settings.os == "Linux":
            self.requires(
                "nativefile-dialog-extended/latest@nisaldilshan/latest")

    def configure(self):
        if self.settings.compiler == "Visual Studio":
            if self.settings.build_type == "Debug":
                self.settings.compiler.runtime = "MDd"
