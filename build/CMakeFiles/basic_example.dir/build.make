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
include CMakeFiles/basic_example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/basic_example.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/basic_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic_example.dir/flags.make

CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o: CMakeFiles/basic_example.dir/flags.make
CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o: /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp
CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o: CMakeFiles/basic_example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o -MF CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o.d -o CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o -c /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp

CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp > CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.i

CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp -o CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.s

# Object files for target basic_example
basic_example_OBJECTS = \
"CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o"

# External object files for target basic_example
basic_example_EXTERNAL_OBJECTS =

basic_example: CMakeFiles/basic_example.dir/chunked_parquet_read_self_implmentation_multi_streams_multi_threads.cpp.o
basic_example: CMakeFiles/basic_example.dir/build.make
basic_example: /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/build/libcudf.so
basic_example: /home/gymeng/anaconda3/envs/rapids-24.04/lib/libarrow.so.1400.2.0
basic_example: /usr/local/cuda-12.1/targets/x86_64-linux/lib/libcudart.so
basic_example: CMakeFiles/basic_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable basic_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic_example.dir/build: basic_example
.PHONY : CMakeFiles/basic_example.dir/build

CMakeFiles/basic_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic_example.dir/clean

CMakeFiles/basic_example.dir/depend:
	cd /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build /home/gymeng/Desktop/cudf/cudf_24.06/cudf/cpp/examples/basic/submit/build/CMakeFiles/basic_example.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/basic_example.dir/depend

