#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import subprocess, fileinput
from conans import ConanFile, CMake, tools

class NativeFileDialogExtendedConan(ConanFile):
    name = "nativefile-dialog-extended"
    version = "latest"
    url = "https://conan.io/center/imguizmo"
    homepage = "https://github.com/btzy/nativefiledialog-extended"
    description = "Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies"
    author = "btzy"
    topics = ("conan", "NativeFileDialog", "FileDialog", "graphical")
    license = "ZLib"
    exports = ["LICENSE.md"]
    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    _source_subfolder = "source_subfolder"

    def source(self):
        git = tools.Git()
        git.clone("https://github.com/btzy/nativefiledialog-extended.git")
        with fileinput.FileInput("CMakeLists.txt", inplace=True, backup='.bak') as file:
            for line in file:
                print(line.replace("set (CMAKE_CXX_STANDARD 23)", ""), end='')

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure()
        cmake.build()

    def package(self):
        self.run('ls')
        self.copy("*.h", "include", "src/include", keep_path=False)
        self.copy("*.a", "lib", "src", keep_path=False)

    def package_info(self):
        gtkflags = subprocess.check_output(['pkg-config', 'gtk+-3.0', '--libs']).decode('utf-8')
        self.cpp_info.libs = ["libnfd.a"]
        self.cpp_info.system_libs = gtkflags.split(" ")
