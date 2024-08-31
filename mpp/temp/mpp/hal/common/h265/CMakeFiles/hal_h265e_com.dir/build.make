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
CMAKE_SOURCE_DIR = /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp

# Include any dependencies generated for this target.
include mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/flags.make

mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o: mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/flags.make
mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o: ../mpp/hal/common/h265/hal_h265e_stream_amend.c
mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o: mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o -MF CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o.d -o CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/common/h265/hal_h265e_stream_amend.c

mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/common/h265/hal_h265e_stream_amend.c > CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.i

mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/common/h265/hal_h265e_stream_amend.c -o CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.s

# Object files for target hal_h265e_com
hal_h265e_com_OBJECTS = \
"CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o"

# External object files for target hal_h265e_com
hal_h265e_com_EXTERNAL_OBJECTS =

mpp/hal/common/h265/libhal_h265e_com.a: mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/hal_h265e_stream_amend.c.o
mpp/hal/common/h265/libhal_h265e_com.a: mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/build.make
mpp/hal/common/h265/libhal_h265e_com.a: mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libhal_h265e_com.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && $(CMAKE_COMMAND) -P CMakeFiles/hal_h265e_com.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hal_h265e_com.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/build: mpp/hal/common/h265/libhal_h265e_com.a
.PHONY : mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/build

mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 && $(CMAKE_COMMAND) -P CMakeFiles/hal_h265e_com.dir/cmake_clean.cmake
.PHONY : mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/clean

mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/common/h265 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/hal/common/h265/CMakeFiles/hal_h265e_com.dir/depend

