# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Assembler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Assembler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Assembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assembler.dir/flags.make

CMakeFiles/Assembler.dir/main.c.obj: CMakeFiles/Assembler.dir/flags.make
CMakeFiles/Assembler.dir/main.c.obj: C:/Users/mohammad/Desktop/Computer-architecture/Assembler\ -\ First\ phase/main.c
CMakeFiles/Assembler.dir/main.c.obj: CMakeFiles/Assembler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Assembler.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Assembler.dir/main.c.obj -MF CMakeFiles\Assembler.dir\main.c.obj.d -o CMakeFiles\Assembler.dir\main.c.obj -c "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\main.c"

CMakeFiles/Assembler.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Assembler.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\main.c" > CMakeFiles\Assembler.dir\main.c.i

CMakeFiles/Assembler.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Assembler.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\main.c" -o CMakeFiles\Assembler.dir\main.c.s

# Object files for target Assembler
Assembler_OBJECTS = \
"CMakeFiles/Assembler.dir/main.c.obj"

# External object files for target Assembler
Assembler_EXTERNAL_OBJECTS =

Assembler.exe: CMakeFiles/Assembler.dir/main.c.obj
Assembler.exe: CMakeFiles/Assembler.dir/build.make
Assembler.exe: CMakeFiles/Assembler.dir/linklibs.rsp
Assembler.exe: CMakeFiles/Assembler.dir/objects1.rsp
Assembler.exe: CMakeFiles/Assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Assembler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Assembler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assembler.dir/build: Assembler.exe
.PHONY : CMakeFiles/Assembler.dir/build

CMakeFiles/Assembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Assembler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Assembler.dir/clean

CMakeFiles/Assembler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase" "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase" "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug" "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug" "C:\Users\mohammad\Desktop\Computer-architecture\Assembler - First phase\cmake-build-debug\CMakeFiles\Assembler.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Assembler.dir/depend

