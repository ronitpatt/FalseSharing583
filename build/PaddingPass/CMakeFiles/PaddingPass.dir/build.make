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
CMAKE_SOURCE_DIR = /home/aryan/Documents/FalseSharing583

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aryan/Documents/FalseSharing583/build

# Include any dependencies generated for this target.
include PaddingPass/CMakeFiles/PaddingPass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include PaddingPass/CMakeFiles/PaddingPass.dir/compiler_depend.make

# Include the progress variables for this target.
include PaddingPass/CMakeFiles/PaddingPass.dir/progress.make

# Include the compile flags for this target's objects.
include PaddingPass/CMakeFiles/PaddingPass.dir/flags.make

PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o: PaddingPass/CMakeFiles/PaddingPass.dir/flags.make
PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o: ../PaddingPass/Pass.cpp
PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o: PaddingPass/CMakeFiles/PaddingPass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aryan/Documents/FalseSharing583/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o"
	cd /home/aryan/Documents/FalseSharing583/build/PaddingPass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o -MF CMakeFiles/PaddingPass.dir/Pass.cpp.o.d -o CMakeFiles/PaddingPass.dir/Pass.cpp.o -c /home/aryan/Documents/FalseSharing583/PaddingPass/Pass.cpp

PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PaddingPass.dir/Pass.cpp.i"
	cd /home/aryan/Documents/FalseSharing583/build/PaddingPass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aryan/Documents/FalseSharing583/PaddingPass/Pass.cpp > CMakeFiles/PaddingPass.dir/Pass.cpp.i

PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PaddingPass.dir/Pass.cpp.s"
	cd /home/aryan/Documents/FalseSharing583/build/PaddingPass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aryan/Documents/FalseSharing583/PaddingPass/Pass.cpp -o CMakeFiles/PaddingPass.dir/Pass.cpp.s

# Object files for target PaddingPass
PaddingPass_OBJECTS = \
"CMakeFiles/PaddingPass.dir/Pass.cpp.o"

# External object files for target PaddingPass
PaddingPass_EXTERNAL_OBJECTS =

PaddingPass/PaddingPass.so: PaddingPass/CMakeFiles/PaddingPass.dir/Pass.cpp.o
PaddingPass/PaddingPass.so: PaddingPass/CMakeFiles/PaddingPass.dir/build.make
PaddingPass/PaddingPass.so: PaddingPass/CMakeFiles/PaddingPass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aryan/Documents/FalseSharing583/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module PaddingPass.so"
	cd /home/aryan/Documents/FalseSharing583/build/PaddingPass && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PaddingPass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
PaddingPass/CMakeFiles/PaddingPass.dir/build: PaddingPass/PaddingPass.so
.PHONY : PaddingPass/CMakeFiles/PaddingPass.dir/build

PaddingPass/CMakeFiles/PaddingPass.dir/clean:
	cd /home/aryan/Documents/FalseSharing583/build/PaddingPass && $(CMAKE_COMMAND) -P CMakeFiles/PaddingPass.dir/cmake_clean.cmake
.PHONY : PaddingPass/CMakeFiles/PaddingPass.dir/clean

PaddingPass/CMakeFiles/PaddingPass.dir/depend:
	cd /home/aryan/Documents/FalseSharing583/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aryan/Documents/FalseSharing583 /home/aryan/Documents/FalseSharing583/PaddingPass /home/aryan/Documents/FalseSharing583/build /home/aryan/Documents/FalseSharing583/build/PaddingPass /home/aryan/Documents/FalseSharing583/build/PaddingPass/CMakeFiles/PaddingPass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PaddingPass/CMakeFiles/PaddingPass.dir/depend

