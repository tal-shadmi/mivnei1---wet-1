# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AVLtree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AVLtree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AVLtree.dir/flags.make

CMakeFiles/AVLtree.dir/main.cpp.obj: CMakeFiles/AVLtree.dir/flags.make
CMakeFiles/AVLtree.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AVLtree.dir/main.cpp.obj"
	C:\TDM-GCC-32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\AVLtree.dir\main.cpp.obj -c C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\main.cpp

CMakeFiles/AVLtree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVLtree.dir/main.cpp.i"
	C:\TDM-GCC-32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\main.cpp > CMakeFiles\AVLtree.dir\main.cpp.i

CMakeFiles/AVLtree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVLtree.dir/main.cpp.s"
	C:\TDM-GCC-32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\main.cpp -o CMakeFiles\AVLtree.dir\main.cpp.s

CMakeFiles/AVLtree.dir/AVLtree.cpp.obj: CMakeFiles/AVLtree.dir/flags.make
CMakeFiles/AVLtree.dir/AVLtree.cpp.obj: ../AVLtree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AVLtree.dir/AVLtree.cpp.obj"
	C:\TDM-GCC-32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\AVLtree.dir\AVLtree.cpp.obj -c C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\AVLtree.cpp

CMakeFiles/AVLtree.dir/AVLtree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVLtree.dir/AVLtree.cpp.i"
	C:\TDM-GCC-32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\AVLtree.cpp > CMakeFiles\AVLtree.dir\AVLtree.cpp.i

CMakeFiles/AVLtree.dir/AVLtree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVLtree.dir/AVLtree.cpp.s"
	C:\TDM-GCC-32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\AVLtree.cpp -o CMakeFiles\AVLtree.dir\AVLtree.cpp.s

# Object files for target AVLtree
AVLtree_OBJECTS = \
"CMakeFiles/AVLtree.dir/main.cpp.obj" \
"CMakeFiles/AVLtree.dir/AVLtree.cpp.obj"

# External object files for target AVLtree
AVLtree_EXTERNAL_OBJECTS =

AVLtree.exe: CMakeFiles/AVLtree.dir/main.cpp.obj
AVLtree.exe: CMakeFiles/AVLtree.dir/AVLtree.cpp.obj
AVLtree.exe: CMakeFiles/AVLtree.dir/build.make
AVLtree.exe: CMakeFiles/AVLtree.dir/linklibs.rsp
AVLtree.exe: CMakeFiles/AVLtree.dir/objects1.rsp
AVLtree.exe: CMakeFiles/AVLtree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AVLtree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AVLtree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AVLtree.dir/build: AVLtree.exe

.PHONY : CMakeFiles/AVLtree.dir/build

CMakeFiles/AVLtree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AVLtree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/AVLtree.dir/clean

CMakeFiles/AVLtree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug C:\Users\Dell\CLionProjects\mivnei1---wet-1\AVLtree\cmake-build-debug\CMakeFiles\AVLtree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AVLtree.dir/depend

