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
CMAKE_SOURCE_DIR = /home/libo/Documents/c++/Mesh_viewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/libo/Documents/c++/Mesh_viewer/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mesh_viewer.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mesh_viewer.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mesh_viewer.dir/flags.make

src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o: src/CMakeFiles/mesh_viewer.dir/flags.make
src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o: ../src/OpenglAlg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/Mesh_viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o   -c /home/libo/Documents/c++/Mesh_viewer/src/OpenglAlg.c

src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesh_viewer.dir/OpenglAlg.c.i"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/Mesh_viewer/src/OpenglAlg.c > CMakeFiles/mesh_viewer.dir/OpenglAlg.c.i

src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesh_viewer.dir/OpenglAlg.c.s"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/Mesh_viewer/src/OpenglAlg.c -o CMakeFiles/mesh_viewer.dir/OpenglAlg.c.s

src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o: src/CMakeFiles/mesh_viewer.dir/flags.make
src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o: ../src/glfw_callback.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/Mesh_viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o -c /home/libo/Documents/c++/Mesh_viewer/src/glfw_callback.cpp

src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.i"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/libo/Documents/c++/Mesh_viewer/src/glfw_callback.cpp > CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.i

src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.s"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/libo/Documents/c++/Mesh_viewer/src/glfw_callback.cpp -o CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.s

src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o: src/CMakeFiles/mesh_viewer.dir/flags.make
src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o: ../thirdpart/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Documents/c++/Mesh_viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o   -c /home/libo/Documents/c++/Mesh_viewer/thirdpart/glad/src/glad.c

src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.i"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Documents/c++/Mesh_viewer/thirdpart/glad/src/glad.c > CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.i

src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.s"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Documents/c++/Mesh_viewer/thirdpart/glad/src/glad.c -o CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.s

# Object files for target mesh_viewer
mesh_viewer_OBJECTS = \
"CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o" \
"CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o" \
"CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o"

# External object files for target mesh_viewer
mesh_viewer_EXTERNAL_OBJECTS =

../temp_libs/libmesh_viewer.a: src/CMakeFiles/mesh_viewer.dir/OpenglAlg.c.o
../temp_libs/libmesh_viewer.a: src/CMakeFiles/mesh_viewer.dir/glfw_callback.cpp.o
../temp_libs/libmesh_viewer.a: src/CMakeFiles/mesh_viewer.dir/__/thirdpart/glad/src/glad.c.o
../temp_libs/libmesh_viewer.a: src/CMakeFiles/mesh_viewer.dir/build.make
../temp_libs/libmesh_viewer.a: src/CMakeFiles/mesh_viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/libo/Documents/c++/Mesh_viewer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../../temp_libs/libmesh_viewer.a"
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mesh_viewer.dir/cmake_clean_target.cmake
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesh_viewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mesh_viewer.dir/build: ../temp_libs/libmesh_viewer.a

.PHONY : src/CMakeFiles/mesh_viewer.dir/build

src/CMakeFiles/mesh_viewer.dir/clean:
	cd /home/libo/Documents/c++/Mesh_viewer/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mesh_viewer.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mesh_viewer.dir/clean

src/CMakeFiles/mesh_viewer.dir/depend:
	cd /home/libo/Documents/c++/Mesh_viewer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/libo/Documents/c++/Mesh_viewer /home/libo/Documents/c++/Mesh_viewer/src /home/libo/Documents/c++/Mesh_viewer/build /home/libo/Documents/c++/Mesh_viewer/build/src /home/libo/Documents/c++/Mesh_viewer/build/src/CMakeFiles/mesh_viewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mesh_viewer.dir/depend
