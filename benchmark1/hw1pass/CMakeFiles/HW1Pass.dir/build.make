# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /n/eecs583a/home/rpatt/Indirection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /n/eecs583a/home/rpatt/Indirection/benchmark1

# Include any dependencies generated for this target.
include hw1pass/CMakeFiles/HW1Pass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include hw1pass/CMakeFiles/HW1Pass.dir/compiler_depend.make

# Include the progress variables for this target.
include hw1pass/CMakeFiles/HW1Pass.dir/progress.make

# Include the compile flags for this target's objects.
include hw1pass/CMakeFiles/HW1Pass.dir/flags.make

hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o: hw1pass/CMakeFiles/HW1Pass.dir/flags.make
hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o: ../hw1pass/hw1pass.cpp
hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o: hw1pass/CMakeFiles/HW1Pass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/n/eecs583a/home/rpatt/Indirection/benchmark1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o"
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o -MF CMakeFiles/HW1Pass.dir/hw1pass.cpp.o.d -o CMakeFiles/HW1Pass.dir/hw1pass.cpp.o -c /n/eecs583a/home/rpatt/Indirection/hw1pass/hw1pass.cpp

hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1Pass.dir/hw1pass.cpp.i"
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /n/eecs583a/home/rpatt/Indirection/hw1pass/hw1pass.cpp > CMakeFiles/HW1Pass.dir/hw1pass.cpp.i

hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1Pass.dir/hw1pass.cpp.s"
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /n/eecs583a/home/rpatt/Indirection/hw1pass/hw1pass.cpp -o CMakeFiles/HW1Pass.dir/hw1pass.cpp.s

# Object files for target HW1Pass
HW1Pass_OBJECTS = \
"CMakeFiles/HW1Pass.dir/hw1pass.cpp.o"

# External object files for target HW1Pass
HW1Pass_EXTERNAL_OBJECTS =

hw1pass/HW1Pass.so: hw1pass/CMakeFiles/HW1Pass.dir/hw1pass.cpp.o
hw1pass/HW1Pass.so: hw1pass/CMakeFiles/HW1Pass.dir/build.make
hw1pass/HW1Pass.so: hw1pass/CMakeFiles/HW1Pass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/n/eecs583a/home/rpatt/Indirection/benchmark1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module HW1Pass.so"
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW1Pass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hw1pass/CMakeFiles/HW1Pass.dir/build: hw1pass/HW1Pass.so
.PHONY : hw1pass/CMakeFiles/HW1Pass.dir/build

hw1pass/CMakeFiles/HW1Pass.dir/clean:
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass && $(CMAKE_COMMAND) -P CMakeFiles/HW1Pass.dir/cmake_clean.cmake
.PHONY : hw1pass/CMakeFiles/HW1Pass.dir/clean

hw1pass/CMakeFiles/HW1Pass.dir/depend:
	cd /n/eecs583a/home/rpatt/Indirection/benchmark1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /n/eecs583a/home/rpatt/Indirection /n/eecs583a/home/rpatt/Indirection/hw1pass /n/eecs583a/home/rpatt/Indirection/benchmark1 /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass /n/eecs583a/home/rpatt/Indirection/benchmark1/hw1pass/CMakeFiles/HW1Pass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hw1pass/CMakeFiles/HW1Pass.dir/depend

