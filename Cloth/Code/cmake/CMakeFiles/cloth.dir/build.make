# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake

# Include any dependencies generated for this target.
include CMakeFiles/cloth.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cloth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cloth.dir/flags.make

CMakeFiles/cloth.dir/src/main.cpp.o: CMakeFiles/cloth.dir/flags.make
CMakeFiles/cloth.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cloth.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cloth.dir/src/main.cpp.o -c /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/src/main.cpp

CMakeFiles/cloth.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cloth.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/src/main.cpp > CMakeFiles/cloth.dir/src/main.cpp.i

CMakeFiles/cloth.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cloth.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/src/main.cpp -o CMakeFiles/cloth.dir/src/main.cpp.s

# Object files for target cloth
cloth_OBJECTS = \
"CMakeFiles/cloth.dir/src/main.cpp.o"

# External object files for target cloth
cloth_EXTERNAL_OBJECTS =

cloth: CMakeFiles/cloth.dir/src/main.cpp.o
cloth: CMakeFiles/cloth.dir/build.make
cloth: /run/media/ezor/LINUX/BookhouseBoys/ezor/libnu/lib/libnu.a
cloth: CMakeFiles/cloth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cloth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cloth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cloth.dir/build: cloth

.PHONY : CMakeFiles/cloth.dir/build

CMakeFiles/cloth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cloth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cloth.dir/clean

CMakeFiles/cloth.dir/depend:
	cd /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake /run/media/ezor/LINUX/BookhouseBoys/ezor/ElasticCloth/Code/cmake/CMakeFiles/cloth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cloth.dir/depend

