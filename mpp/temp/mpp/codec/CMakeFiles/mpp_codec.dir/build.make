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
include mpp/codec/CMakeFiles/mpp_codec.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/codec/CMakeFiles/mpp_codec.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/codec/CMakeFiles/mpp_codec.dir/flags.make

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o: ../mpp/codec/mpp_enc_impl.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_impl.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_impl.cpp > CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_impl.cpp -o CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o: ../mpp/codec/mpp_enc_v2.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_v2.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_v2.cpp > CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_enc_v2.cpp -o CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o: ../mpp/codec/enc_impl.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o -MF CMakeFiles/mpp_codec.dir/enc_impl.cpp.o.d -o CMakeFiles/mpp_codec.dir/enc_impl.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc_impl.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/enc_impl.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc_impl.cpp > CMakeFiles/mpp_codec.dir/enc_impl.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/enc_impl.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/enc_impl.cpp -o CMakeFiles/mpp_codec.dir/enc_impl.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o: ../mpp/codec/mpp_dec_no_thread.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_no_thread.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_no_thread.cpp > CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_no_thread.cpp -o CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o: ../mpp/codec/mpp_dec_normal.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_normal.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_normal.cpp > CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec_normal.cpp -o CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o: ../mpp/codec/mpp_dec.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_dec.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec.cpp > CMakeFiles/mpp_codec.dir/mpp_dec.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_dec.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_dec.cpp -o CMakeFiles/mpp_codec.dir/mpp_dec.cpp.s

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/flags.make
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o: ../mpp/codec/mpp_parser.cpp
mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o: mpp/codec/CMakeFiles/mpp_codec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o -MF CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o.d -o CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_parser.cpp

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpp_codec.dir/mpp_parser.cpp.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_parser.cpp > CMakeFiles/mpp_codec.dir/mpp_parser.cpp.i

mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpp_codec.dir/mpp_parser.cpp.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec/mpp_parser.cpp -o CMakeFiles/mpp_codec.dir/mpp_parser.cpp.s

# Object files for target mpp_codec
mpp_codec_OBJECTS = \
"CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o" \
"CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o" \
"CMakeFiles/mpp_codec.dir/enc_impl.cpp.o" \
"CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o" \
"CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o" \
"CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o" \
"CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o"

# External object files for target mpp_codec
mpp_codec_EXTERNAL_OBJECTS =

mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_impl.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_enc_v2.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/enc_impl.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_no_thread.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec_normal.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_dec.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/mpp_parser.cpp.o
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/build.make
mpp/codec/libmpp_codec.a: mpp/codec/CMakeFiles/mpp_codec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libmpp_codec.a"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && $(CMAKE_COMMAND) -P CMakeFiles/mpp_codec.dir/cmake_clean_target.cmake
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpp_codec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/codec/CMakeFiles/mpp_codec.dir/build: mpp/codec/libmpp_codec.a
.PHONY : mpp/codec/CMakeFiles/mpp_codec.dir/build

mpp/codec/CMakeFiles/mpp_codec.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec && $(CMAKE_COMMAND) -P CMakeFiles/mpp_codec.dir/cmake_clean.cmake
.PHONY : mpp/codec/CMakeFiles/mpp_codec.dir/clean

mpp/codec/CMakeFiles/mpp_codec.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/codec /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/codec/CMakeFiles/mpp_codec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/codec/CMakeFiles/mpp_codec.dir/depend

