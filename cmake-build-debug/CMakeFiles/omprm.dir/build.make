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
CMAKE_COMMAND = /cygdrive/c/Users/BMI24/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/BMI24/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/BMI24/CLionProjects/omprm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/omprm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/omprm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/omprm.dir/flags.make

CMakeFiles/omprm.dir/main.cpp.o: CMakeFiles/omprm.dir/flags.make
CMakeFiles/omprm.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/omprm.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/omprm.dir/main.cpp.o -c /cygdrive/c/Users/BMI24/CLionProjects/omprm/main.cpp

CMakeFiles/omprm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/omprm.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/BMI24/CLionProjects/omprm/main.cpp > CMakeFiles/omprm.dir/main.cpp.i

CMakeFiles/omprm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/omprm.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/BMI24/CLionProjects/omprm/main.cpp -o CMakeFiles/omprm.dir/main.cpp.s

CMakeFiles/omprm.dir/ray_marcher.cpp.o: CMakeFiles/omprm.dir/flags.make
CMakeFiles/omprm.dir/ray_marcher.cpp.o: ../ray_marcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/omprm.dir/ray_marcher.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/omprm.dir/ray_marcher.cpp.o -c /cygdrive/c/Users/BMI24/CLionProjects/omprm/ray_marcher.cpp

CMakeFiles/omprm.dir/ray_marcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/omprm.dir/ray_marcher.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/BMI24/CLionProjects/omprm/ray_marcher.cpp > CMakeFiles/omprm.dir/ray_marcher.cpp.i

CMakeFiles/omprm.dir/ray_marcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/omprm.dir/ray_marcher.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/BMI24/CLionProjects/omprm/ray_marcher.cpp -o CMakeFiles/omprm.dir/ray_marcher.cpp.s

# Object files for target omprm
omprm_OBJECTS = \
"CMakeFiles/omprm.dir/main.cpp.o" \
"CMakeFiles/omprm.dir/ray_marcher.cpp.o"

# External object files for target omprm
omprm_EXTERNAL_OBJECTS =

omprm.exe: CMakeFiles/omprm.dir/main.cpp.o
omprm.exe: CMakeFiles/omprm.dir/ray_marcher.cpp.o
omprm.exe: CMakeFiles/omprm.dir/build.make
omprm.exe: CMakeFiles/omprm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable omprm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/omprm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/omprm.dir/build: omprm.exe

.PHONY : CMakeFiles/omprm.dir/build

CMakeFiles/omprm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/omprm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/omprm.dir/clean

CMakeFiles/omprm.dir/depend:
	cd /cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/BMI24/CLionProjects/omprm /cygdrive/c/Users/BMI24/CLionProjects/omprm /cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug /cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug /cygdrive/c/Users/BMI24/CLionProjects/omprm/cmake-build-debug/CMakeFiles/omprm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/omprm.dir/depend

