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
include mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/flags.make

mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o: mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/flags.make
mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o: ../mpp/hal/vpu/av1d/hal_av1d_vdpu.c
mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o: mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o -MF CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o.d -o CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/vpu/av1d/hal_av1d_vdpu.c

mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/vpu/av1d/hal_av1d_vdpu.c > CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.i

mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/vpu/av1d/hal_av1d_vdpu.c -o CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.s

# Object files for target hal_av1d_vpu
hal_av1d_vpu_OBJECTS = \
"CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o"

# External object files for target hal_av1d_vpu
hal_av1d_vpu_EXTERNAL_OBJECTS =

mpp/hal/vpu/av1d/libhal_av1d_vpu.a: mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/hal_av1d_vdpu.c.o
mpp/hal/vpu/av1d/libhal_av1d_vpu.a: mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/build.make
mpp/hal/vpu/av1d/libhal_av1d_vpu.a: mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libhal_av1d_vpu.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && $(CMAKE_COMMAND) -P CMakeFiles/hal_av1d_vpu.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hal_av1d_vpu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/build: mpp/hal/vpu/av1d/libhal_av1d_vpu.a
.PHONY : mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/build

mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d && $(CMAKE_COMMAND) -P CMakeFiles/hal_av1d_vpu.dir/cmake_clean.cmake
.PHONY : mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/clean

mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/hal/vpu/av1d /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/hal/vpu/av1d/CMakeFiles/hal_av1d_vpu.dir/depend

