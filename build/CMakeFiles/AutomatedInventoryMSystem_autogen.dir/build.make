# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build"

# Utility rule file for AutomatedInventoryMSystem_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/AutomatedInventoryMSystem_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AutomatedInventoryMSystem_autogen.dir/progress.make

CMakeFiles/AutomatedInventoryMSystem_autogen: AutomatedInventoryMSystem_autogen/timestamp

AutomatedInventoryMSystem_autogen/timestamp: /opt/homebrew/share/qt/libexec/moc
AutomatedInventoryMSystem_autogen/timestamp: /opt/homebrew/share/qt/libexec/uic
AutomatedInventoryMSystem_autogen/timestamp: CMakeFiles/AutomatedInventoryMSystem_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target AutomatedInventoryMSystem"
	/opt/homebrew/bin/cmake -E cmake_autogen "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build/CMakeFiles/AutomatedInventoryMSystem_autogen.dir/AutogenInfo.json" ""
	/opt/homebrew/bin/cmake -E touch "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build/AutomatedInventoryMSystem_autogen/timestamp"

CMakeFiles/AutomatedInventoryMSystem_autogen.dir/codegen:
.PHONY : CMakeFiles/AutomatedInventoryMSystem_autogen.dir/codegen

AutomatedInventoryMSystem_autogen: AutomatedInventoryMSystem_autogen/timestamp
AutomatedInventoryMSystem_autogen: CMakeFiles/AutomatedInventoryMSystem_autogen
AutomatedInventoryMSystem_autogen: CMakeFiles/AutomatedInventoryMSystem_autogen.dir/build.make
.PHONY : AutomatedInventoryMSystem_autogen

# Rule to build all files generated by this target.
CMakeFiles/AutomatedInventoryMSystem_autogen.dir/build: AutomatedInventoryMSystem_autogen
.PHONY : CMakeFiles/AutomatedInventoryMSystem_autogen.dir/build

CMakeFiles/AutomatedInventoryMSystem_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AutomatedInventoryMSystem_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AutomatedInventoryMSystem_autogen.dir/clean

CMakeFiles/AutomatedInventoryMSystem_autogen.dir/depend:
	cd "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem" "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem" "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build" "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build" "/Users/prathamgauswami/Desktop/SIDE PROJECTS/CPP/AutomatedInventoryMSystem/build/CMakeFiles/AutomatedInventoryMSystem_autogen.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/AutomatedInventoryMSystem_autogen.dir/depend

