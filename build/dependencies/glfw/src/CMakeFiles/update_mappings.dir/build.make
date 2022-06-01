# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = "/C/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "/C/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /C/Users/johnp/Documents/GitHub/Thighs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /C/Users/johnp/Documents/GitHub/Thighs/build

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include dependencies/glfw/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include dependencies/glfw/src/CMakeFiles/update_mappings.dir/progress.make

dependencies/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/C/Users/johnp/Documents/GitHub/Thighs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd /C/Users/johnp/Documents/GitHub/Thighs/dependencies/glfw/src && "/C/Program Files/CMake/bin/cmake.exe" -P C:/Users/johnp/Documents/GitHub/Thighs/dependencies/glfw/CMake/GenerateMappings.cmake mappings.h.in mappings.h

update_mappings: dependencies/glfw/src/CMakeFiles/update_mappings
update_mappings: dependencies/glfw/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
dependencies/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : dependencies/glfw/src/CMakeFiles/update_mappings.dir/build

dependencies/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd /C/Users/johnp/Documents/GitHub/Thighs/build/dependencies/glfw/src && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : dependencies/glfw/src/CMakeFiles/update_mappings.dir/clean

dependencies/glfw/src/CMakeFiles/update_mappings.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /C/Users/johnp/Documents/GitHub/Thighs /C/Users/johnp/Documents/GitHub/Thighs/dependencies/glfw/src /C/Users/johnp/Documents/GitHub/Thighs/build /C/Users/johnp/Documents/GitHub/Thighs/build/dependencies/glfw/src /C/Users/johnp/Documents/GitHub/Thighs/build/dependencies/glfw/src/CMakeFiles/update_mappings.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies/glfw/src/CMakeFiles/update_mappings.dir/depend

