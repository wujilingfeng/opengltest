# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/libo/Documents/c++/Viewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/libo/Documents/c++/Viewer/build

# Include any dependencies generated for this target.
include src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/depend.make

# Include the progress variables for this target.
include src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/progress.make

# Include the compile flags for this target's objects.
include src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/flags.make

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/flags.make
src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o: ../src/Math/Mesh_viewer_math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/Viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o   -c /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_math.c

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.i"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_math.c > CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.i

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.s"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_math.c -o CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.s

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/flags.make
src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o: ../src/Math/Mesh_viewer_matrix4x4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/Viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o   -c /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_matrix4x4.c

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.i"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_matrix4x4.c > CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.i

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.s"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/Viewer/src/Math/Mesh_viewer_matrix4x4.c -o CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.s

# Object files for target mesh_viewer_matrix4x4
mesh_viewer_matrix4x4_OBJECTS = \
"CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o" \
"CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o"

# External object files for target mesh_viewer_matrix4x4
mesh_viewer_matrix4x4_EXTERNAL_OBJECTS =

../temp_libs/libmesh_viewer_matrix4x4.a: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_math.c.o
../temp_libs/libmesh_viewer_matrix4x4.a: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/Mesh_viewer_matrix4x4.c.o
../temp_libs/libmesh_viewer_matrix4x4.a: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/build.make
../temp_libs/libmesh_viewer_matrix4x4.a: src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/libo/Documents/c++/Viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library ../../../temp_libs/libmesh_viewer_matrix4x4.a"
	cd /home/libo/Documents/c++/Viewer/build/src/Math && $(CMAKE_COMMAND) -P CMakeFiles/mesh_viewer_matrix4x4.dir/cmake_clean_target.cmake
	cd /home/libo/Documents/c++/Viewer/build/src/Math && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesh_viewer_matrix4x4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/build: ../temp_libs/libmesh_viewer_matrix4x4.a

.PHONY : src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/build

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/clean:
	cd /home/libo/Documents/c++/Viewer/build/src/Math && $(CMAKE_COMMAND) -P CMakeFiles/mesh_viewer_matrix4x4.dir/cmake_clean.cmake
.PHONY : src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/clean

src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/depend:
	cd /home/libo/Documents/c++/Viewer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/libo/Documents/c++/Viewer /home/libo/Documents/c++/Viewer/src/Math /home/libo/Documents/c++/Viewer/build /home/libo/Documents/c++/Viewer/build/src/Math /home/libo/Documents/c++/Viewer/build/src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Math/CMakeFiles/mesh_viewer_matrix4x4.dir/depend

