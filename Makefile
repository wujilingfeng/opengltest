# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/libo/Documents/c++/Viewer1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/libo/Documents/c++/Viewer1.0

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/libo/Documents/c++/Viewer1.0/CMakeFiles /home/libo/Documents/c++/Viewer1.0/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/libo/Documents/c++/Viewer1.0/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

#=============================================================================
# Target rules for targets named viewer

# Build rule for target.
viewer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 viewer
.PHONY : viewer

# fast build rule for target.
viewer/fast:
	$(MAKE) -f src/CMakeFiles/viewer.dir/build.make src/CMakeFiles/viewer.dir/build
.PHONY : viewer/fast

#=============================================================================
# Target rules for targets named viewer_matrix4x4

# Build rule for target.
viewer_matrix4x4: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 viewer_matrix4x4
.PHONY : viewer_matrix4x4

# fast build rule for target.
viewer_matrix4x4/fast:
	$(MAKE) -f src/Math/CMakeFiles/viewer_matrix4x4.dir/build.make src/Math/CMakeFiles/viewer_matrix4x4.dir/build
.PHONY : viewer_matrix4x4/fast

#=============================================================================
# Target rules for targets named viewer_openglalg

# Build rule for target.
viewer_openglalg: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 viewer_openglalg
.PHONY : viewer_openglalg

# fast build rule for target.
viewer_openglalg/fast:
	$(MAKE) -f src/Viewer_Interpreter/OpenGL/CMakeFiles/viewer_openglalg.dir/build.make src/Viewer_Interpreter/OpenGL/CMakeFiles/viewer_openglalg.dir/build
.PHONY : viewer_openglalg/fast

#=============================================================================
# Target rules for targets named viewer_world_manager

# Build rule for target.
viewer_world_manager: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 viewer_world_manager
.PHONY : viewer_world_manager

# fast build rule for target.
viewer_world_manager/fast:
	$(MAKE) -f src/Viewer_World_Manager/CMakeFiles/viewer_world_manager.dir/build.make src/Viewer_World_Manager/CMakeFiles/viewer_world_manager.dir/build
.PHONY : viewer_world_manager/fast

Demo/Arcroll.o: Demo/Arcroll.c.o

.PHONY : Demo/Arcroll.o

# target to build an object file
Demo/Arcroll.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/Arcroll.c.o
.PHONY : Demo/Arcroll.c.o

Demo/Arcroll.i: Demo/Arcroll.c.i

.PHONY : Demo/Arcroll.i

# target to preprocess a source file
Demo/Arcroll.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/Arcroll.c.i
.PHONY : Demo/Arcroll.c.i

Demo/Arcroll.s: Demo/Arcroll.c.s

.PHONY : Demo/Arcroll.s

# target to generate assembly for a file
Demo/Arcroll.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/Arcroll.c.s
.PHONY : Demo/Arcroll.c.s

Demo/main.o: Demo/main.cpp.o

.PHONY : Demo/main.o

# target to build an object file
Demo/main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/main.cpp.o
.PHONY : Demo/main.cpp.o

Demo/main.i: Demo/main.cpp.i

.PHONY : Demo/main.i

# target to preprocess a source file
Demo/main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/main.cpp.i
.PHONY : Demo/main.cpp.i

Demo/main.s: Demo/main.cpp.s

.PHONY : Demo/main.s

# target to generate assembly for a file
Demo/main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/Demo/main.cpp.s
.PHONY : Demo/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install/local"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... viewer"
	@echo "... viewer_matrix4x4"
	@echo "... viewer_openglalg"
	@echo "... viewer_world_manager"
	@echo "... Demo/Arcroll.o"
	@echo "... Demo/Arcroll.i"
	@echo "... Demo/Arcroll.s"
	@echo "... Demo/main.o"
	@echo "... Demo/main.i"
	@echo "... Demo/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
