# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/picolesp.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/picolesp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/picolesp.dir/flags.make

CMakeFiles/picolesp.dir/archive/networking.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/archive/networking.cpp.o: ../archive/networking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/picolesp.dir/archive/networking.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/archive/networking.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/networking.cpp

CMakeFiles/picolesp.dir/archive/networking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/archive/networking.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/networking.cpp > CMakeFiles/picolesp.dir/archive/networking.cpp.i

CMakeFiles/picolesp.dir/archive/networking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/archive/networking.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/networking.cpp -o CMakeFiles/picolesp.dir/archive/networking.cpp.s

CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o: ../archive/picol_glue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/picol_glue.cpp

CMakeFiles/picolesp.dir/archive/picol_glue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/archive/picol_glue.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/picol_glue.cpp > CMakeFiles/picolesp.dir/archive/picol_glue.cpp.i

CMakeFiles/picolesp.dir/archive/picol_glue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/archive/picol_glue.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/archive/picol_glue.cpp -o CMakeFiles/picolesp.dir/archive/picol_glue.cpp.s

CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o: ../cloud_mqqt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cloud_mqqt.cpp

CMakeFiles/picolesp.dir/cloud_mqqt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/cloud_mqqt.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cloud_mqqt.cpp > CMakeFiles/picolesp.dir/cloud_mqqt.cpp.i

CMakeFiles/picolesp.dir/cloud_mqqt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/cloud_mqqt.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cloud_mqqt.cpp -o CMakeFiles/picolesp.dir/cloud_mqqt.cpp.s

CMakeFiles/picolesp.dir/debug2.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/debug2.cpp.o: ../debug2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/picolesp.dir/debug2.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/debug2.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/debug2.cpp

CMakeFiles/picolesp.dir/debug2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/debug2.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/debug2.cpp > CMakeFiles/picolesp.dir/debug2.cpp.i

CMakeFiles/picolesp.dir/debug2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/debug2.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/debug2.cpp -o CMakeFiles/picolesp.dir/debug2.cpp.s

CMakeFiles/picolesp.dir/esp_relay.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/esp_relay.cpp.o: ../esp_relay.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/picolesp.dir/esp_relay.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/esp_relay.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/esp_relay.cpp

CMakeFiles/picolesp.dir/esp_relay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/esp_relay.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/esp_relay.cpp > CMakeFiles/picolesp.dir/esp_relay.cpp.i

CMakeFiles/picolesp.dir/esp_relay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/esp_relay.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/esp_relay.cpp -o CMakeFiles/picolesp.dir/esp_relay.cpp.s

CMakeFiles/picolesp.dir/led_status.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/led_status.cpp.o: ../led_status.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/picolesp.dir/led_status.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/led_status.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/led_status.cpp

CMakeFiles/picolesp.dir/led_status.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/led_status.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/led_status.cpp > CMakeFiles/picolesp.dir/led_status.cpp.i

CMakeFiles/picolesp.dir/led_status.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/led_status.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/led_status.cpp -o CMakeFiles/picolesp.dir/led_status.cpp.s

CMakeFiles/picolesp.dir/logger.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/logger.cpp.o: ../logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/picolesp.dir/logger.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/logger.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/logger.cpp

CMakeFiles/picolesp.dir/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/logger.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/logger.cpp > CMakeFiles/picolesp.dir/logger.cpp.i

CMakeFiles/picolesp.dir/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/logger.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/logger.cpp -o CMakeFiles/picolesp.dir/logger.cpp.s

CMakeFiles/picolesp.dir/picol_glue.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/picol_glue.cpp.o: ../picol_glue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/picolesp.dir/picol_glue.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/picol_glue.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/picol_glue.cpp

CMakeFiles/picolesp.dir/picol_glue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/picol_glue.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/picol_glue.cpp > CMakeFiles/picolesp.dir/picol_glue.cpp.i

CMakeFiles/picolesp.dir/picol_glue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/picol_glue.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/picol_glue.cpp -o CMakeFiles/picolesp.dir/picol_glue.cpp.s

CMakeFiles/picolesp.dir/static_storage.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/static_storage.cpp.o: ../static_storage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/picolesp.dir/static_storage.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/static_storage.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/static_storage.cpp

CMakeFiles/picolesp.dir/static_storage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/static_storage.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/static_storage.cpp > CMakeFiles/picolesp.dir/static_storage.cpp.i

CMakeFiles/picolesp.dir/static_storage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/static_storage.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/static_storage.cpp -o CMakeFiles/picolesp.dir/static_storage.cpp.s

CMakeFiles/picolesp.dir/subscriptions.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/subscriptions.cpp.o: ../subscriptions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/picolesp.dir/subscriptions.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/subscriptions.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/subscriptions.cpp

CMakeFiles/picolesp.dir/subscriptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/subscriptions.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/subscriptions.cpp > CMakeFiles/picolesp.dir/subscriptions.cpp.i

CMakeFiles/picolesp.dir/subscriptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/subscriptions.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/subscriptions.cpp -o CMakeFiles/picolesp.dir/subscriptions.cpp.s

CMakeFiles/picolesp.dir/clock_timer.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/clock_timer.cpp.o: ../clock_timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/picolesp.dir/clock_timer.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/clock_timer.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/clock_timer.cpp

CMakeFiles/picolesp.dir/clock_timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/clock_timer.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/clock_timer.cpp > CMakeFiles/picolesp.dir/clock_timer.cpp.i

CMakeFiles/picolesp.dir/clock_timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/clock_timer.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/clock_timer.cpp -o CMakeFiles/picolesp.dir/clock_timer.cpp.s

CMakeFiles/picolesp.dir/event.cpp.o: CMakeFiles/picolesp.dir/flags.make
CMakeFiles/picolesp.dir/event.cpp.o: ../event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/picolesp.dir/event.cpp.o"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/picolesp.dir/event.cpp.o -c /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/event.cpp

CMakeFiles/picolesp.dir/event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/picolesp.dir/event.cpp.i"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/event.cpp > CMakeFiles/picolesp.dir/event.cpp.i

CMakeFiles/picolesp.dir/event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/picolesp.dir/event.cpp.s"
	/Applications/Xcode_11.3.1_fb.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/event.cpp -o CMakeFiles/picolesp.dir/event.cpp.s

# Object files for target picolesp
picolesp_OBJECTS = \
"CMakeFiles/picolesp.dir/archive/networking.cpp.o" \
"CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o" \
"CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o" \
"CMakeFiles/picolesp.dir/debug2.cpp.o" \
"CMakeFiles/picolesp.dir/esp_relay.cpp.o" \
"CMakeFiles/picolesp.dir/led_status.cpp.o" \
"CMakeFiles/picolesp.dir/logger.cpp.o" \
"CMakeFiles/picolesp.dir/picol_glue.cpp.o" \
"CMakeFiles/picolesp.dir/static_storage.cpp.o" \
"CMakeFiles/picolesp.dir/subscriptions.cpp.o" \
"CMakeFiles/picolesp.dir/clock_timer.cpp.o" \
"CMakeFiles/picolesp.dir/event.cpp.o"

# External object files for target picolesp
picolesp_EXTERNAL_OBJECTS =

picolesp: CMakeFiles/picolesp.dir/archive/networking.cpp.o
picolesp: CMakeFiles/picolesp.dir/archive/picol_glue.cpp.o
picolesp: CMakeFiles/picolesp.dir/cloud_mqqt.cpp.o
picolesp: CMakeFiles/picolesp.dir/debug2.cpp.o
picolesp: CMakeFiles/picolesp.dir/esp_relay.cpp.o
picolesp: CMakeFiles/picolesp.dir/led_status.cpp.o
picolesp: CMakeFiles/picolesp.dir/logger.cpp.o
picolesp: CMakeFiles/picolesp.dir/picol_glue.cpp.o
picolesp: CMakeFiles/picolesp.dir/static_storage.cpp.o
picolesp: CMakeFiles/picolesp.dir/subscriptions.cpp.o
picolesp: CMakeFiles/picolesp.dir/clock_timer.cpp.o
picolesp: CMakeFiles/picolesp.dir/event.cpp.o
picolesp: CMakeFiles/picolesp.dir/build.make
picolesp: CMakeFiles/picolesp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable picolesp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/picolesp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/picolesp.dir/build: picolesp
.PHONY : CMakeFiles/picolesp.dir/build

CMakeFiles/picolesp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/picolesp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/picolesp.dir/clean

CMakeFiles/picolesp.dir/depend:
	cd /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug /Users/johnsalwitz/Documents/MyStuff/GitHub/picolesp/cmake-build-debug/CMakeFiles/picolesp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/picolesp.dir/depend

