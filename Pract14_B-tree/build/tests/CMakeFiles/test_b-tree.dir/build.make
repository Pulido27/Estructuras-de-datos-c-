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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_b-tree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_b-tree.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_b-tree.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_b-tree.dir/flags.make

tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o: tests/CMakeFiles/test_b-tree.dir/flags.make
tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o: /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/tests/test_b-tree.cpp
tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o: tests/CMakeFiles/test_b-tree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o"
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o -MF CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o.d -o CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o -c /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/tests/test_b-tree.cpp

tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_b-tree.dir/test_b-tree.cpp.i"
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/tests/test_b-tree.cpp > CMakeFiles/test_b-tree.dir/test_b-tree.cpp.i

tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_b-tree.dir/test_b-tree.cpp.s"
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/tests/test_b-tree.cpp -o CMakeFiles/test_b-tree.dir/test_b-tree.cpp.s

# Object files for target test_b-tree
test_b__tree_OBJECTS = \
"CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o"

# External object files for target test_b-tree
test_b__tree_EXTERNAL_OBJECTS =

tests/test_b-tree: tests/CMakeFiles/test_b-tree.dir/test_b-tree.cpp.o
tests/test_b-tree: tests/CMakeFiles/test_b-tree.dir/build.make
tests/test_b-tree: tests/CMakeFiles/test_b-tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_b-tree"
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_b-tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_b-tree.dir/build: tests/test_b-tree
.PHONY : tests/CMakeFiles/test_b-tree.dir/build

tests/CMakeFiles/test_b-tree.dir/clean:
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_b-tree.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_b-tree.dir/clean

tests/CMakeFiles/test_b-tree.dir/depend:
	cd /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/tests /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests /home/ubuntu/Proyectos/Estructuras-de-datos-c-/Pract14_B-tree/build/tests/CMakeFiles/test_b-tree.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/test_b-tree.dir/depend

