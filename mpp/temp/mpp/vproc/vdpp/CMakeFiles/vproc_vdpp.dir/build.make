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
include mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/flags.make

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/flags.make
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o: ../mpp/vproc/vdpp/vdpp_api.c
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o -MF CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o.d -o CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_api.c

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vproc_vdpp.dir/vdpp_api.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_api.c > CMakeFiles/vproc_vdpp.dir/vdpp_api.c.i

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vproc_vdpp.dir/vdpp_api.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_api.c -o CMakeFiles/vproc_vdpp.dir/vdpp_api.c.s

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/flags.make
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o: ../mpp/vproc/vdpp/vdpp.c
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o -MF CMakeFiles/vproc_vdpp.dir/vdpp.c.o.d -o CMakeFiles/vproc_vdpp.dir/vdpp.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp.c

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vproc_vdpp.dir/vdpp.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp.c > CMakeFiles/vproc_vdpp.dir/vdpp.c.i

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vproc_vdpp.dir/vdpp.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp.c -o CMakeFiles/vproc_vdpp.dir/vdpp.c.s

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/flags.make
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o: ../mpp/vproc/vdpp/vdpp2.c
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o -MF CMakeFiles/vproc_vdpp.dir/vdpp2.c.o.d -o CMakeFiles/vproc_vdpp.dir/vdpp2.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp2.c

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vproc_vdpp.dir/vdpp2.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp2.c > CMakeFiles/vproc_vdpp.dir/vdpp2.c.i

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vproc_vdpp.dir/vdpp2.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp2.c -o CMakeFiles/vproc_vdpp.dir/vdpp2.c.s

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/flags.make
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o: ../mpp/vproc/vdpp/vdpp_common.c
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o -MF CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o.d -o CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_common.c

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vproc_vdpp.dir/vdpp_common.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_common.c > CMakeFiles/vproc_vdpp.dir/vdpp_common.c.i

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vproc_vdpp.dir/vdpp_common.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp/vdpp_common.c -o CMakeFiles/vproc_vdpp.dir/vdpp_common.c.s

# Object files for target vproc_vdpp
vproc_vdpp_OBJECTS = \
"CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o" \
"CMakeFiles/vproc_vdpp.dir/vdpp.c.o" \
"CMakeFiles/vproc_vdpp.dir/vdpp2.c.o" \
"CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o"

# External object files for target vproc_vdpp
vproc_vdpp_EXTERNAL_OBJECTS =

mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_api.c.o
mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp.c.o
mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp2.c.o
mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/vdpp_common.c.o
mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/build.make
mpp/vproc/vdpp/libvproc_vdpp.a: mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libvproc_vdpp.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && $(CMAKE_COMMAND) -P CMakeFiles/vproc_vdpp.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vproc_vdpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/build: mpp/vproc/vdpp/libvproc_vdpp.a
.PHONY : mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/build

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp && $(CMAKE_COMMAND) -P CMakeFiles/vproc_vdpp.dir/cmake_clean.cmake
.PHONY : mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/clean

mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/vproc/vdpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/vproc/vdpp/CMakeFiles/vproc_vdpp.dir/depend

