# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build

# Include any dependencies generated for this target.
include _deps/gtest-build/googletest/CMakeFiles/gtest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/gtest-build/googletest/CMakeFiles/gtest.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/gtest-build/googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/gtest-build/googletest/CMakeFiles/gtest.dir/flags.make

_deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/gtest-build/googletest/CMakeFiles/gtest.dir/flags.make
_deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/gtest-src/googletest/src/gtest-all.cc
_deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/gtest-build/googletest/CMakeFiles/gtest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o -MF CMakeFiles/gtest.dir/src/gtest-all.cc.o.d -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-src/googletest/src/gtest-all.cc

_deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-src/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

_deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-src/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

lib/libgtest.a: _deps/gtest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
lib/libgtest.a: _deps/gtest-build/googletest/CMakeFiles/gtest.dir/build.make
lib/libgtest.a: _deps/gtest-build/googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libgtest.a"
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/gtest-build/googletest/CMakeFiles/gtest.dir/build: lib/libgtest.a
.PHONY : _deps/gtest-build/googletest/CMakeFiles/gtest.dir/build

_deps/gtest-build/googletest/CMakeFiles/gtest.dir/clean:
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : _deps/gtest-build/googletest/CMakeFiles/gtest.dir/clean

_deps/gtest-build/googletest/CMakeFiles/gtest.dir/depend:
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-src/googletest /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/_deps/gtest-build/googletest/CMakeFiles/gtest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/gtest-build/googletest/CMakeFiles/gtest.dir/depend

