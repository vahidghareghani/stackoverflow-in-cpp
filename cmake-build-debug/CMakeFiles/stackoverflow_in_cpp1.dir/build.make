# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/spsina/Desktop/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/spsina/Desktop/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/spsina/CLionProjects/stackoverflow-in-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/stackoverflow_in_cpp1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stackoverflow_in_cpp1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stackoverflow_in_cpp1.dir/flags.make

CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o: CMakeFiles/stackoverflow_in_cpp1.dir/flags.make
CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o -c /home/spsina/CLionProjects/stackoverflow-in-cpp/main.cpp

CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spsina/CLionProjects/stackoverflow-in-cpp/main.cpp > CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.i

CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spsina/CLionProjects/stackoverflow-in-cpp/main.cpp -o CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.s

CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o: CMakeFiles/stackoverflow_in_cpp1.dir/flags.make
CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o: ../User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o -c /home/spsina/CLionProjects/stackoverflow-in-cpp/User.cpp

CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spsina/CLionProjects/stackoverflow-in-cpp/User.cpp > CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.i

CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spsina/CLionProjects/stackoverflow-in-cpp/User.cpp -o CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.s

# Object files for target stackoverflow_in_cpp1
stackoverflow_in_cpp1_OBJECTS = \
"CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o" \
"CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o"

# External object files for target stackoverflow_in_cpp1
stackoverflow_in_cpp1_EXTERNAL_OBJECTS =

stackoverflow_in_cpp1: CMakeFiles/stackoverflow_in_cpp1.dir/main.cpp.o
stackoverflow_in_cpp1: CMakeFiles/stackoverflow_in_cpp1.dir/User.cpp.o
stackoverflow_in_cpp1: CMakeFiles/stackoverflow_in_cpp1.dir/build.make
stackoverflow_in_cpp1: CMakeFiles/stackoverflow_in_cpp1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable stackoverflow_in_cpp1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stackoverflow_in_cpp1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stackoverflow_in_cpp1.dir/build: stackoverflow_in_cpp1

.PHONY : CMakeFiles/stackoverflow_in_cpp1.dir/build

CMakeFiles/stackoverflow_in_cpp1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stackoverflow_in_cpp1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stackoverflow_in_cpp1.dir/clean

CMakeFiles/stackoverflow_in_cpp1.dir/depend:
	cd /home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spsina/CLionProjects/stackoverflow-in-cpp /home/spsina/CLionProjects/stackoverflow-in-cpp /home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug /home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug /home/spsina/CLionProjects/stackoverflow-in-cpp/cmake-build-debug/CMakeFiles/stackoverflow_in_cpp1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stackoverflow_in_cpp1.dir/depend

