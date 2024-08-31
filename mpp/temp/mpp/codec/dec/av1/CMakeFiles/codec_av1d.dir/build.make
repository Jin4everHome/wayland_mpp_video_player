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
include mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o: ../mpp/codec/dec/av1/av1d_api.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o -MF CMakeFiles/codec_av1d.dir/av1d_api.c.o.d -o CMakeFiles/codec_av1d.dir/av1d_api.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_api.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1d_api.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_api.c > CMakeFiles/codec_av1d.dir/av1d_api.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1d_api.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_api.c -o CMakeFiles/codec_av1d.dir/av1d_api.c.s

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o: ../mpp/codec/dec/av1/av1d_parser.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o -MF CMakeFiles/codec_av1d.dir/av1d_parser.c.o.d -o CMakeFiles/codec_av1d.dir/av1d_parser.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1d_parser.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser.c > CMakeFiles/codec_av1d.dir/av1d_parser.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1d_parser.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser.c -o CMakeFiles/codec_av1d.dir/av1d_parser.c.s

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o: ../mpp/codec/dec/av1/av1d_parser2_syntax.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o -MF CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o.d -o CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser2_syntax.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser2_syntax.c > CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_parser2_syntax.c -o CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.s

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o: ../mpp/codec/dec/av1/av1d_cbs.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o -MF CMakeFiles/codec_av1d.dir/av1d_cbs.c.o.d -o CMakeFiles/codec_av1d.dir/av1d_cbs.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_cbs.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1d_cbs.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_cbs.c > CMakeFiles/codec_av1d.dir/av1d_cbs.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1d_cbs.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_cbs.c -o CMakeFiles/codec_av1d.dir/av1d_cbs.c.s

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o: ../mpp/codec/dec/av1/av1d_probs.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o -MF CMakeFiles/codec_av1d.dir/av1d_probs.c.o.d -o CMakeFiles/codec_av1d.dir/av1d_probs.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_probs.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1d_probs.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_probs.c > CMakeFiles/codec_av1d.dir/av1d_probs.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1d_probs.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1d_probs.c -o CMakeFiles/codec_av1d.dir/av1d_probs.c.s

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/flags.make
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o: ../mpp/codec/dec/av1/av1_entropymode.c
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o -MF CMakeFiles/codec_av1d.dir/av1_entropymode.c.o.d -o CMakeFiles/codec_av1d.dir/av1_entropymode.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1_entropymode.c

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/codec_av1d.dir/av1_entropymode.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1_entropymode.c > CMakeFiles/codec_av1d.dir/av1_entropymode.c.i

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/codec_av1d.dir/av1_entropymode.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1/av1_entropymode.c -o CMakeFiles/codec_av1d.dir/av1_entropymode.c.s

# Object files for target codec_av1d
codec_av1d_OBJECTS = \
"CMakeFiles/codec_av1d.dir/av1d_api.c.o" \
"CMakeFiles/codec_av1d.dir/av1d_parser.c.o" \
"CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o" \
"CMakeFiles/codec_av1d.dir/av1d_cbs.c.o" \
"CMakeFiles/codec_av1d.dir/av1d_probs.c.o" \
"CMakeFiles/codec_av1d.dir/av1_entropymode.c.o"

# External object files for target codec_av1d
codec_av1d_EXTERNAL_OBJECTS =

mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_api.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_parser2_syntax.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_cbs.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1d_probs.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/av1_entropymode.c.o
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/build.make
mpp/codec/dec/av1/libcodec_av1d.a: mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libcodec_av1d.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && $(CMAKE_COMMAND) -P CMakeFiles/codec_av1d.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/codec_av1d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/build: mpp/codec/dec/av1/libcodec_av1d.a
.PHONY : mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/build

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 && $(CMAKE_COMMAND) -P CMakeFiles/codec_av1d.dir/cmake_clean.cmake
.PHONY : mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/clean

mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/dec/av1 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1 /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/codec/dec/av1/CMakeFiles/codec_av1d.dir/depend

