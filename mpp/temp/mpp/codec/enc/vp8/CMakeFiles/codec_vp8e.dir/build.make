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
include mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/flags.make

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/flags.make
mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o: ../mpp/codec/enc/vp8/vp8e_api_v2.c
mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o -MF CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o.d -o CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_api_v2.c

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_api_v2.c > CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.i

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_api_v2.c -o CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.s

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/flags.make
mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o: ../mpp/codec/enc/vp8/vp8e_rc.c
mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o -MF CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o.d -o CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_rc.c

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_vp8e.dir/vp8e_rc.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_rc.c > CMakeFiles/codec_vp8e.dir/vp8e_rc.c.i

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_vp8e.dir/vp8e_rc.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8/vp8e_rc.c -o CMakeFiles/codec_vp8e.dir/vp8e_rc.c.s

# Object files for target codec_vp8e
codec_vp8e_OBJECTS = \
"CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o" \
"CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o"

# External object files for target codec_vp8e
codec_vp8e_EXTERNAL_OBJECTS =

mpp/codec/enc/vp8/libcodec_vp8e.a: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_api_v2.c.o
mpp/codec/enc/vp8/libcodec_vp8e.a: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/vp8e_rc.c.o
mpp/codec/enc/vp8/libcodec_vp8e.a: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/build.make
mpp/codec/enc/vp8/libcodec_vp8e.a: mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcodec_vp8e.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && $(CMAKE_COMMAND) -P CMakeFiles/codec_vp8e.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/codec_vp8e.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/build: mpp/codec/enc/vp8/libcodec_vp8e.a
.PHONY : mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/build

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 && $(CMAKE_COMMAND) -P CMakeFiles/codec_vp8e.dir/cmake_clean.cmake
.PHONY : mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/clean

mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc/vp8 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/codec/enc/vp8/CMakeFiles/codec_vp8e.dir/depend

