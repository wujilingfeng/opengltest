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
CMAKE_SOURCE_DIR = /home/libo/Downloads/glfw-3.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/libo/Downloads/glfw-3.3/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/icon.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/icon.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/icon.dir/flags.make

tests/CMakeFiles/icon.dir/icon.c.o: tests/CMakeFiles/icon.dir/flags.make
tests/CMakeFiles/icon.dir/icon.c.o: ../tests/icon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Downloads/glfw-3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/icon.dir/icon.c.o"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icon.dir/icon.c.o   -c /home/libo/Downloads/glfw-3.3/tests/icon.c

tests/CMakeFiles/icon.dir/icon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icon.dir/icon.c.i"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Downloads/glfw-3.3/tests/icon.c > CMakeFiles/icon.dir/icon.c.i

tests/CMakeFiles/icon.dir/icon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icon.dir/icon.c.s"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Downloads/glfw-3.3/tests/icon.c -o CMakeFiles/icon.dir/icon.c.s

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/icon.dir/flags.make
tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o: ../deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/libo/Downloads/glfw-3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/icon.dir/__/deps/glad_gl.c.o   -c /home/libo/Downloads/glfw-3.3/deps/glad_gl.c

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/icon.dir/__/deps/glad_gl.c.i"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/libo/Downloads/glfw-3.3/deps/glad_gl.c > CMakeFiles/icon.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/icon.dir/__/deps/glad_gl.c.s"
	cd /home/libo/Downloads/glfw-3.3/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/libo/Downloads/glfw-3.3/deps/glad_gl.c -o CMakeFiles/icon.dir/__/deps/glad_gl.c.s

# Object files for target icon
icon_OBJECTS = \
"CMakeFiles/icon.dir/icon.c.o" \
"CMakeFiles/icon.dir/__/deps/glad_gl.c.o"

# External object files for target icon
icon_EXTERNAL_OBJECTS =

tests/icon: tests/CMakeFiles/icon.dir/icon.c.o
tests/icon: tests/CMakeFiles/icon.dir/__/deps/glad_gl.c.o
tests/icon: tests/CMakeFiles/icon.dir/build.make
tests/icon: src/libglfw3.a
tests/icon: /usr/lib/x86_64-linux-gnu/libm.so
tests/icon: /usr/lib/x86_64-linux-gnu/librt.so
tests/icon: /usr/lib/x86_64-linux-gnu/libm.so
tests/icon: /usr/lib/x86_64-linux-gnu/libX11.so
tests/icon: tests/CMakeFiles/icon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/libo/Downloads/glfw-3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable icon"
	cd /home/libo/Downloads/glfw-3.3/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/icon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/icon.dir/build: tests/icon

.PHONY : tests/CMakeFiles/icon.dir/build

tests/CMakeFiles/icon.dir/clean:
	cd /home/libo/Downloads/glfw-3.3/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/icon.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/icon.dir/clean

tests/CMakeFiles/icon.dir/depend:
	cd /home/libo/Downloads/glfw-3.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/libo/Downloads/glfw-3.3 /home/libo/Downloads/glfw-3.3/tests /home/libo/Downloads/glfw-3.3/build /home/libo/Downloads/glfw-3.3/build/tests /home/libo/Downloads/glfw-3.3/build/tests/CMakeFiles/icon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/icon.dir/depend

