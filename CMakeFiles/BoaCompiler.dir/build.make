# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alireza/Documents/Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alireza/Documents/Compiler

# Include any dependencies generated for this target.
include CMakeFiles/BoaCompiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BoaCompiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BoaCompiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BoaCompiler.dir/flags.make

CMakeFiles/BoaCompiler.dir/code/Compilers.c.o: CMakeFiles/BoaCompiler.dir/flags.make
CMakeFiles/BoaCompiler.dir/code/Compilers.c.o: code/Compilers.c
CMakeFiles/BoaCompiler.dir/code/Compilers.c.o: CMakeFiles/BoaCompiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alireza/Documents/Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BoaCompiler.dir/code/Compilers.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BoaCompiler.dir/code/Compilers.c.o -MF CMakeFiles/BoaCompiler.dir/code/Compilers.c.o.d -o CMakeFiles/BoaCompiler.dir/code/Compilers.c.o -c /home/alireza/Documents/Compiler/code/Compilers.c

CMakeFiles/BoaCompiler.dir/code/Compilers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BoaCompiler.dir/code/Compilers.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alireza/Documents/Compiler/code/Compilers.c > CMakeFiles/BoaCompiler.dir/code/Compilers.c.i

CMakeFiles/BoaCompiler.dir/code/Compilers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BoaCompiler.dir/code/Compilers.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alireza/Documents/Compiler/code/Compilers.c -o CMakeFiles/BoaCompiler.dir/code/Compilers.c.s

CMakeFiles/BoaCompiler.dir/code/MainReader.c.o: CMakeFiles/BoaCompiler.dir/flags.make
CMakeFiles/BoaCompiler.dir/code/MainReader.c.o: code/MainReader.c
CMakeFiles/BoaCompiler.dir/code/MainReader.c.o: CMakeFiles/BoaCompiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alireza/Documents/Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/BoaCompiler.dir/code/MainReader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BoaCompiler.dir/code/MainReader.c.o -MF CMakeFiles/BoaCompiler.dir/code/MainReader.c.o.d -o CMakeFiles/BoaCompiler.dir/code/MainReader.c.o -c /home/alireza/Documents/Compiler/code/MainReader.c

CMakeFiles/BoaCompiler.dir/code/MainReader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BoaCompiler.dir/code/MainReader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alireza/Documents/Compiler/code/MainReader.c > CMakeFiles/BoaCompiler.dir/code/MainReader.c.i

CMakeFiles/BoaCompiler.dir/code/MainReader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BoaCompiler.dir/code/MainReader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alireza/Documents/Compiler/code/MainReader.c -o CMakeFiles/BoaCompiler.dir/code/MainReader.c.s

CMakeFiles/BoaCompiler.dir/code/Reader.c.o: CMakeFiles/BoaCompiler.dir/flags.make
CMakeFiles/BoaCompiler.dir/code/Reader.c.o: code/Reader.c
CMakeFiles/BoaCompiler.dir/code/Reader.c.o: CMakeFiles/BoaCompiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alireza/Documents/Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/BoaCompiler.dir/code/Reader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BoaCompiler.dir/code/Reader.c.o -MF CMakeFiles/BoaCompiler.dir/code/Reader.c.o.d -o CMakeFiles/BoaCompiler.dir/code/Reader.c.o -c /home/alireza/Documents/Compiler/code/Reader.c

CMakeFiles/BoaCompiler.dir/code/Reader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BoaCompiler.dir/code/Reader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alireza/Documents/Compiler/code/Reader.c > CMakeFiles/BoaCompiler.dir/code/Reader.c.i

CMakeFiles/BoaCompiler.dir/code/Reader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BoaCompiler.dir/code/Reader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alireza/Documents/Compiler/code/Reader.c -o CMakeFiles/BoaCompiler.dir/code/Reader.c.s

# Object files for target BoaCompiler
BoaCompiler_OBJECTS = \
"CMakeFiles/BoaCompiler.dir/code/Compilers.c.o" \
"CMakeFiles/BoaCompiler.dir/code/MainReader.c.o" \
"CMakeFiles/BoaCompiler.dir/code/Reader.c.o"

# External object files for target BoaCompiler
BoaCompiler_EXTERNAL_OBJECTS =

BoaCompiler: CMakeFiles/BoaCompiler.dir/code/Compilers.c.o
BoaCompiler: CMakeFiles/BoaCompiler.dir/code/MainReader.c.o
BoaCompiler: CMakeFiles/BoaCompiler.dir/code/Reader.c.o
BoaCompiler: CMakeFiles/BoaCompiler.dir/build.make
BoaCompiler: CMakeFiles/BoaCompiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alireza/Documents/Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable BoaCompiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BoaCompiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BoaCompiler.dir/build: BoaCompiler
.PHONY : CMakeFiles/BoaCompiler.dir/build

CMakeFiles/BoaCompiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BoaCompiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BoaCompiler.dir/clean

CMakeFiles/BoaCompiler.dir/depend:
	cd /home/alireza/Documents/Compiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alireza/Documents/Compiler /home/alireza/Documents/Compiler /home/alireza/Documents/Compiler /home/alireza/Documents/Compiler /home/alireza/Documents/Compiler/CMakeFiles/BoaCompiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BoaCompiler.dir/depend

