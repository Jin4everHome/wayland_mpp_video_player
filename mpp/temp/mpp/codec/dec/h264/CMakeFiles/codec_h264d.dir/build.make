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
include mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o: ../mpp/codec/dec/h264/h264d_api.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o -MF CMakeFiles/codec_h264d.dir/h264d_api.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_api.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_api.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_api.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_api.c > CMakeFiles/codec_h264d.dir/h264d_api.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_api.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_api.c -o CMakeFiles/codec_h264d.dir/h264d_api.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o: ../mpp/codec/dec/h264/h264d_parse.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o -MF CMakeFiles/codec_h264d.dir/h264d_parse.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_parse.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_parse.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_parse.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_parse.c > CMakeFiles/codec_h264d.dir/h264d_parse.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_parse.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_parse.c -o CMakeFiles/codec_h264d.dir/h264d_parse.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o: ../mpp/codec/dec/h264/h264d_slice.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o -MF CMakeFiles/codec_h264d.dir/h264d_slice.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_slice.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_slice.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_slice.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_slice.c > CMakeFiles/codec_h264d.dir/h264d_slice.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_slice.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_slice.c -o CMakeFiles/codec_h264d.dir/h264d_slice.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o: ../mpp/codec/dec/h264/h264d_sps.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o -MF CMakeFiles/codec_h264d.dir/h264d_sps.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_sps.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sps.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_sps.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sps.c > CMakeFiles/codec_h264d.dir/h264d_sps.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_sps.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sps.c -o CMakeFiles/codec_h264d.dir/h264d_sps.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o: ../mpp/codec/dec/h264/h264d_pps.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o -MF CMakeFiles/codec_h264d.dir/h264d_pps.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_pps.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_pps.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_pps.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_pps.c > CMakeFiles/codec_h264d.dir/h264d_pps.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_pps.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_pps.c -o CMakeFiles/codec_h264d.dir/h264d_pps.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o: ../mpp/codec/dec/h264/h264d_scalist.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o -MF CMakeFiles/codec_h264d.dir/h264d_scalist.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_scalist.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_scalist.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_scalist.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_scalist.c > CMakeFiles/codec_h264d.dir/h264d_scalist.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_scalist.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_scalist.c -o CMakeFiles/codec_h264d.dir/h264d_scalist.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o: ../mpp/codec/dec/h264/h264d_sei.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o -MF CMakeFiles/codec_h264d.dir/h264d_sei.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_sei.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sei.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_sei.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sei.c > CMakeFiles/codec_h264d.dir/h264d_sei.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_sei.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_sei.c -o CMakeFiles/codec_h264d.dir/h264d_sei.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o: ../mpp/codec/dec/h264/h264d_dpb.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o -MF CMakeFiles/codec_h264d.dir/h264d_dpb.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_dpb.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_dpb.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_dpb.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_dpb.c > CMakeFiles/codec_h264d.dir/h264d_dpb.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_dpb.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_dpb.c -o CMakeFiles/codec_h264d.dir/h264d_dpb.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o: ../mpp/codec/dec/h264/h264d_init.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o -MF CMakeFiles/codec_h264d.dir/h264d_init.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_init.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_init.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_init.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_init.c > CMakeFiles/codec_h264d.dir/h264d_init.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_init.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_init.c -o CMakeFiles/codec_h264d.dir/h264d_init.c.s

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/flags.make
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o: ../mpp/codec/dec/h264/h264d_fill.c
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o -MF CMakeFiles/codec_h264d.dir/h264d_fill.c.o.d -o CMakeFiles/codec_h264d.dir/h264d_fill.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_fill.c

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_h264d.dir/h264d_fill.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_fill.c > CMakeFiles/codec_h264d.dir/h264d_fill.c.i

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_h264d.dir/h264d_fill.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264/h264d_fill.c -o CMakeFiles/codec_h264d.dir/h264d_fill.c.s

# Object files for target codec_h264d
codec_h264d_OBJECTS = \
"CMakeFiles/codec_h264d.dir/h264d_api.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_parse.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_slice.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_sps.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_pps.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_scalist.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_sei.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_dpb.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_init.c.o" \
"CMakeFiles/codec_h264d.dir/h264d_fill.c.o"

# External object files for target codec_h264d
codec_h264d_EXTERNAL_OBJECTS =

mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_api.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_parse.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_slice.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sps.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_pps.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_scalist.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_sei.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_dpb.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_init.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/h264d_fill.c.o
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/build.make
mpp/codec/dec/h264/libcodec_h264d.a: mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libcodec_h264d.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && $(CMAKE_COMMAND) -P CMakeFiles/codec_h264d.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/codec_h264d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/build: mpp/codec/dec/h264/libcodec_h264d.a
.PHONY : mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/build

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 && $(CMAKE_COMMAND) -P CMakeFiles/codec_h264d.dir/cmake_clean.cmake
.PHONY : mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/clean

mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/h264 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/codec/dec/h264/CMakeFiles/codec_h264d.dir/depend

