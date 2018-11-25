from conans import ConanFile, CMake


class AudiotoolkitConan(ConanFile):
    name = "Audio-ToolKit"
    version = "3.1.0"
    license = "BSD"
    author = "Matthieu Brucher <matthieu.brucher@gmail.com>"
    url = "https://www.github.com/mbrucher/AudioTK"
    description = "<Description of Audiotoolkit here>"
    topics = ("Audio Processing", "DSP", "Pipeline")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake"
    exports_sources = "ATK/*"
    requires = ("boost/1.68.0@conan/stable")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["ENABLE_PYTHON"] = "OFF"
        cmake.definitions["ENABLE_GPL"] = "ON"
        cmake.configure(source_folder=".")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/ATK", src="ATK")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["hello"]
