# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/goncalofreitas/Desktop/CG/Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/goncalofreitas/Desktop/CG/build

# Include any dependencies generated for this target.
include CMakeFiles/phase2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/phase2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/phase2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/phase2.dir/flags.make

CMakeFiles/phase2.dir/engine.cpp.o: CMakeFiles/phase2.dir/flags.make
CMakeFiles/phase2.dir/engine.cpp.o: /Users/goncalofreitas/Desktop/CG/Engine/engine.cpp
CMakeFiles/phase2.dir/engine.cpp.o: CMakeFiles/phase2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/phase2.dir/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/phase2.dir/engine.cpp.o -MF CMakeFiles/phase2.dir/engine.cpp.o.d -o CMakeFiles/phase2.dir/engine.cpp.o -c /Users/goncalofreitas/Desktop/CG/Engine/engine.cpp

CMakeFiles/phase2.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase2.dir/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/goncalofreitas/Desktop/CG/Engine/engine.cpp > CMakeFiles/phase2.dir/engine.cpp.i

CMakeFiles/phase2.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase2.dir/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/goncalofreitas/Desktop/CG/Engine/engine.cpp -o CMakeFiles/phase2.dir/engine.cpp.s

CMakeFiles/phase2.dir/tinyxml2.cpp.o: CMakeFiles/phase2.dir/flags.make
CMakeFiles/phase2.dir/tinyxml2.cpp.o: /Users/goncalofreitas/Desktop/CG/Engine/tinyxml2.cpp
CMakeFiles/phase2.dir/tinyxml2.cpp.o: CMakeFiles/phase2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/phase2.dir/tinyxml2.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/phase2.dir/tinyxml2.cpp.o -MF CMakeFiles/phase2.dir/tinyxml2.cpp.o.d -o CMakeFiles/phase2.dir/tinyxml2.cpp.o -c /Users/goncalofreitas/Desktop/CG/Engine/tinyxml2.cpp

CMakeFiles/phase2.dir/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase2.dir/tinyxml2.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/goncalofreitas/Desktop/CG/Engine/tinyxml2.cpp > CMakeFiles/phase2.dir/tinyxml2.cpp.i

CMakeFiles/phase2.dir/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase2.dir/tinyxml2.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/goncalofreitas/Desktop/CG/Engine/tinyxml2.cpp -o CMakeFiles/phase2.dir/tinyxml2.cpp.s

CMakeFiles/phase2.dir/figure.cpp.o: CMakeFiles/phase2.dir/flags.make
CMakeFiles/phase2.dir/figure.cpp.o: /Users/goncalofreitas/Desktop/CG/Engine/figure.cpp
CMakeFiles/phase2.dir/figure.cpp.o: CMakeFiles/phase2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/phase2.dir/figure.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/phase2.dir/figure.cpp.o -MF CMakeFiles/phase2.dir/figure.cpp.o.d -o CMakeFiles/phase2.dir/figure.cpp.o -c /Users/goncalofreitas/Desktop/CG/Engine/figure.cpp

CMakeFiles/phase2.dir/figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase2.dir/figure.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/goncalofreitas/Desktop/CG/Engine/figure.cpp > CMakeFiles/phase2.dir/figure.cpp.i

CMakeFiles/phase2.dir/figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase2.dir/figure.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/goncalofreitas/Desktop/CG/Engine/figure.cpp -o CMakeFiles/phase2.dir/figure.cpp.s

CMakeFiles/phase2.dir/ponto.cpp.o: CMakeFiles/phase2.dir/flags.make
CMakeFiles/phase2.dir/ponto.cpp.o: /Users/goncalofreitas/Desktop/CG/Engine/ponto.cpp
CMakeFiles/phase2.dir/ponto.cpp.o: CMakeFiles/phase2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/phase2.dir/ponto.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/phase2.dir/ponto.cpp.o -MF CMakeFiles/phase2.dir/ponto.cpp.o.d -o CMakeFiles/phase2.dir/ponto.cpp.o -c /Users/goncalofreitas/Desktop/CG/Engine/ponto.cpp

CMakeFiles/phase2.dir/ponto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase2.dir/ponto.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/goncalofreitas/Desktop/CG/Engine/ponto.cpp > CMakeFiles/phase2.dir/ponto.cpp.i

CMakeFiles/phase2.dir/ponto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase2.dir/ponto.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/goncalofreitas/Desktop/CG/Engine/ponto.cpp -o CMakeFiles/phase2.dir/ponto.cpp.s

CMakeFiles/phase2.dir/transformacao.cpp.o: CMakeFiles/phase2.dir/flags.make
CMakeFiles/phase2.dir/transformacao.cpp.o: /Users/goncalofreitas/Desktop/CG/Engine/transformacao.cpp
CMakeFiles/phase2.dir/transformacao.cpp.o: CMakeFiles/phase2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/phase2.dir/transformacao.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/phase2.dir/transformacao.cpp.o -MF CMakeFiles/phase2.dir/transformacao.cpp.o.d -o CMakeFiles/phase2.dir/transformacao.cpp.o -c /Users/goncalofreitas/Desktop/CG/Engine/transformacao.cpp

CMakeFiles/phase2.dir/transformacao.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase2.dir/transformacao.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/goncalofreitas/Desktop/CG/Engine/transformacao.cpp > CMakeFiles/phase2.dir/transformacao.cpp.i

CMakeFiles/phase2.dir/transformacao.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase2.dir/transformacao.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/goncalofreitas/Desktop/CG/Engine/transformacao.cpp -o CMakeFiles/phase2.dir/transformacao.cpp.s

# Object files for target phase2
phase2_OBJECTS = \
"CMakeFiles/phase2.dir/engine.cpp.o" \
"CMakeFiles/phase2.dir/tinyxml2.cpp.o" \
"CMakeFiles/phase2.dir/figure.cpp.o" \
"CMakeFiles/phase2.dir/ponto.cpp.o" \
"CMakeFiles/phase2.dir/transformacao.cpp.o"

# External object files for target phase2
phase2_EXTERNAL_OBJECTS =

phase2: CMakeFiles/phase2.dir/engine.cpp.o
phase2: CMakeFiles/phase2.dir/tinyxml2.cpp.o
phase2: CMakeFiles/phase2.dir/figure.cpp.o
phase2: CMakeFiles/phase2.dir/ponto.cpp.o
phase2: CMakeFiles/phase2.dir/transformacao.cpp.o
phase2: CMakeFiles/phase2.dir/build.make
phase2: CMakeFiles/phase2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/goncalofreitas/Desktop/CG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable phase2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/phase2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/phase2.dir/build: phase2
.PHONY : CMakeFiles/phase2.dir/build

CMakeFiles/phase2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/phase2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/phase2.dir/clean

CMakeFiles/phase2.dir/depend:
	cd /Users/goncalofreitas/Desktop/CG/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/goncalofreitas/Desktop/CG/Engine /Users/goncalofreitas/Desktop/CG/Engine /Users/goncalofreitas/Desktop/CG/build /Users/goncalofreitas/Desktop/CG/build /Users/goncalofreitas/Desktop/CG/build/CMakeFiles/phase2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/phase2.dir/depend

