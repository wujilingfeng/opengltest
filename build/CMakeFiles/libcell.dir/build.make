# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\program\cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\program\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\libcell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\libcell\build

# Include any dependencies generated for this target.
include CMakeFiles/libcell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libcell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libcell.dir/flags.make

CMakeFiles/libcell.dir/src/Arcroll.cpp.obj: CMakeFiles/libcell.dir/flags.make
CMakeFiles/libcell.dir/src/Arcroll.cpp.obj: CMakeFiles/libcell.dir/includes_CXX.rsp
CMakeFiles/libcell.dir/src/Arcroll.cpp.obj: ../src/Arcroll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libcell.dir/src/Arcroll.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\libcell.dir\src\Arcroll.cpp.obj -c D:\code\libcell\src\Arcroll.cpp

CMakeFiles/libcell.dir/src/Arcroll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libcell.dir/src/Arcroll.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\libcell\src\Arcroll.cpp > CMakeFiles\libcell.dir\src\Arcroll.cpp.i

CMakeFiles/libcell.dir/src/Arcroll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libcell.dir/src/Arcroll.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\libcell\src\Arcroll.cpp -o CMakeFiles\libcell.dir\src\Arcroll.cpp.s

CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj: CMakeFiles/libcell.dir/flags.make
CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj: CMakeFiles/libcell.dir/includes_CXX.rsp
CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj: ../src/OpenglAlg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\libcell.dir\src\OpenglAlg.cpp.obj -c D:\code\libcell\src\OpenglAlg.cpp

CMakeFiles/libcell.dir/src/OpenglAlg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libcell.dir/src/OpenglAlg.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\libcell\src\OpenglAlg.cpp > CMakeFiles\libcell.dir\src\OpenglAlg.cpp.i

CMakeFiles/libcell.dir/src/OpenglAlg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libcell.dir/src/OpenglAlg.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\libcell\src\OpenglAlg.cpp -o CMakeFiles\libcell.dir\src\OpenglAlg.cpp.s

CMakeFiles/libcell.dir/src/glad.c.obj: CMakeFiles/libcell.dir/flags.make
CMakeFiles/libcell.dir/src/glad.c.obj: CMakeFiles/libcell.dir/includes_C.rsp
CMakeFiles/libcell.dir/src/glad.c.obj: ../src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/libcell.dir/src/glad.c.obj"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\libcell.dir\src\glad.c.obj   -c D:\code\libcell\src\glad.c

CMakeFiles/libcell.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libcell.dir/src/glad.c.i"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\code\libcell\src\glad.c > CMakeFiles\libcell.dir\src\glad.c.i

CMakeFiles/libcell.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libcell.dir/src/glad.c.s"
	D:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\code\libcell\src\glad.c -o CMakeFiles\libcell.dir\src\glad.c.s

CMakeFiles/libcell.dir/src/libcell.cpp.obj: CMakeFiles/libcell.dir/flags.make
CMakeFiles/libcell.dir/src/libcell.cpp.obj: CMakeFiles/libcell.dir/includes_CXX.rsp
CMakeFiles/libcell.dir/src/libcell.cpp.obj: ../src/libcell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/libcell.dir/src/libcell.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\libcell.dir\src\libcell.cpp.obj -c D:\code\libcell\src\libcell.cpp

CMakeFiles/libcell.dir/src/libcell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libcell.dir/src/libcell.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\libcell\src\libcell.cpp > CMakeFiles\libcell.dir\src\libcell.cpp.i

CMakeFiles/libcell.dir/src/libcell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libcell.dir/src/libcell.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\libcell\src\libcell.cpp -o CMakeFiles\libcell.dir\src\libcell.cpp.s

CMakeFiles/libcell.dir/src/tools_node.cpp.obj: CMakeFiles/libcell.dir/flags.make
CMakeFiles/libcell.dir/src/tools_node.cpp.obj: CMakeFiles/libcell.dir/includes_CXX.rsp
CMakeFiles/libcell.dir/src/tools_node.cpp.obj: ../src/tools_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/libcell.dir/src/tools_node.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\libcell.dir\src\tools_node.cpp.obj -c D:\code\libcell\src\tools_node.cpp

CMakeFiles/libcell.dir/src/tools_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libcell.dir/src/tools_node.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\libcell\src\tools_node.cpp > CMakeFiles\libcell.dir\src\tools_node.cpp.i

CMakeFiles/libcell.dir/src/tools_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libcell.dir/src/tools_node.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\libcell\src\tools_node.cpp -o CMakeFiles\libcell.dir\src\tools_node.cpp.s

# Object files for target libcell
libcell_OBJECTS = \
"CMakeFiles/libcell.dir/src/Arcroll.cpp.obj" \
"CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj" \
"CMakeFiles/libcell.dir/src/glad.c.obj" \
"CMakeFiles/libcell.dir/src/libcell.cpp.obj" \
"CMakeFiles/libcell.dir/src/tools_node.cpp.obj"

# External object files for target libcell
libcell_EXTERNAL_OBJECTS =

libcell.exe: CMakeFiles/libcell.dir/src/Arcroll.cpp.obj
libcell.exe: CMakeFiles/libcell.dir/src/OpenglAlg.cpp.obj
libcell.exe: CMakeFiles/libcell.dir/src/glad.c.obj
libcell.exe: CMakeFiles/libcell.dir/src/libcell.cpp.obj
libcell.exe: CMakeFiles/libcell.dir/src/tools_node.cpp.obj
libcell.exe: CMakeFiles/libcell.dir/build.make
libcell.exe: CMakeFiles/libcell.dir/linklibs.rsp
libcell.exe: CMakeFiles/libcell.dir/objects1.rsp
libcell.exe: CMakeFiles/libcell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\libcell\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable libcell.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\libcell.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libcell.dir/build: libcell.exe

.PHONY : CMakeFiles/libcell.dir/build

CMakeFiles/libcell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\libcell.dir\cmake_clean.cmake
.PHONY : CMakeFiles/libcell.dir/clean

CMakeFiles/libcell.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\libcell D:\code\libcell D:\code\libcell\build D:\code\libcell\build D:\code\libcell\build\CMakeFiles\libcell.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libcell.dir/depend

