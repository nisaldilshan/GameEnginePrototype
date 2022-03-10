#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
from conans import ConanFile, CMake, tools


class ImGuizmoConan(ConanFile):
    name = "imguizmo"
    version = "latest"
    url = "https://conan.io/center/imguizmo"
    homepage = "https://github.com:TheCherno/ImGuizmo"
    description = "Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies"
    author = "Cherno"
    topics = ("conan", "imguizmo", "gizmo", "graphical")
    license = "MIT"
    exports = ["LICENSE.md"]
    exports_sources = ["CMakeLists.txt", ]
    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    _source_subfolder = "source_subfolder"

    def source(self):
        git = tools.Git(folder=self._source_subfolder)
        git.clone("https://github.com/TheCherno/ImGuizmo.git")


    def package(self):
        self.copy(pattern="ImGuizmo.h", dst="include", src=self._source_subfolder, keep_path=False)
        self.copy(pattern="ImGuizmo.cpp", dst="include", src=self._source_subfolder, keep_path=False)


