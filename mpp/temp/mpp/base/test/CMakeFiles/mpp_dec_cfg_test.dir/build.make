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
include mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/compiler_depend.make

# Include the progress variables for this target.
include mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/progress.make

# Include the compile flags for this target's objects.
include mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/flags.make

mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o: mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/flags.make
mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o: ../mpp/base/test/mpp_dec_cfg_test.c
mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o: mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o -MF CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o.d -o CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o -c /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/base/test/mpp_dec_cfg_test.c

mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.i"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/base/test/mpp_dec_cfg_test.c > CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.i

mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.s"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test && /opt/amlogic/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/base/test/mpp_dec_cfg_test.c -o CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.s

# Object files for target mpp_dec_cfg_test
mpp_dec_cfg_test_OBJECTS = \
"CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o"

# External object files for target mpp_dec_cfg_test
mpp_dec_cfg_test_EXTERNAL_OBJECTS =

mpp/base/test/mpp_dec_cfg_test: mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/mpp_dec_cfg_test.c.o
mpp/base/test/mpp_dec_cfg_test: mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/build.make
mpp/base/test/mpp_dec_cfg_test: mpp/librockchip_mpp.so.0
mpp/base/test/mpp_dec_cfg_test: mpp/codec/libmpp_codec.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/avs/libcodec_avsd.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/avs2/libcodec_avs2d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/h263/libcodec_h263d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/h264/libcodec_h264d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/h265/libcodec_h265d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/common/libdec_common.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/m2v/libcodec_mpeg2d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/mpg4/libcodec_mpeg4d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/vp8/libcodec_vp8d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/vp9/libcodec_vp9d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/jpeg/libcodec_jpegd.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/av1/libcodec_av1d.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/enc/jpeg/libcodec_jpege.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/enc/h265/libcodec_h265e.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/enc/vp8/libcodec_vp8e.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/enc/dummy/libcodec_dummy_enc.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/dec/dummy/libcodec_dummy_dec.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/libmpp_hal.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/h264d/libhal_h264d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/libmpp_hal.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/h264d/libhal_h264d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/avsd/libhal_avsd.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/avs2d/libhal_avs2d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/h263d/libhal_h263d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/h265d/libhal_h265d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/m2vd/libhal_mpeg2d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/mpg4d/libhal_mpeg4d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/vp8d/libhal_vp8d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/vp9d/libhal_vp9d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/jpegd/libhal_jpegd.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/av1/libhal_av1d.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/av1d/libhal_av1d_rkv.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/av1d/libhal_av1d_vpu.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/av1/libhal_av1d_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/h264/libhal_h264e.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkenc/h264e/libhal_h264e_rkv.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/h264e/libhal_h264e_vpu.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/enc/h264/libcodec_h264e.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/rc/libenc_rc.a
mpp/base/test/mpp_dec_cfg_test: mpp/codec/libmpp_rc.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/h264/libhal_h264e_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/jpeg/libhal_jpege.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkenc/jpege/libhal_jpege_rkv.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/jpeg/libhal_jpege_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/jpege/libhal_jpege_vpu.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/h265/libhal_h265e.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkenc/h265e/libhal_h265e_vepu541.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/h265/libhal_h265e_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkenc/h265e/libhal_h265e_vepu541.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/h265/libhal_h265e_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkenc/common/libhal_vepu541_common.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/common/libhal_common.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/vp8e/libhal_vp8e.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/vpu/common/libhal_vepu_common.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/dummy/libhal_dummy.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/libvdpu383_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/hal/rkdec/libvdpu34x_com.a
mpp/base/test/mpp_dec_cfg_test: mpp/vproc/libmpp_vproc.a
mpp/base/test/mpp_dec_cfg_test: mpp/vproc/rga/libvproc_rga.a
mpp/base/test/mpp_dec_cfg_test: mpp/vproc/iep/libvproc_iep.a
mpp/base/test/mpp_dec_cfg_test: mpp/vproc/iep2/libvproc_iep2.a
mpp/base/test/mpp_dec_cfg_test: mpp/base/libmpp_base.a
mpp/base/test/mpp_dec_cfg_test: osal/libosal.a
mpp/base/test/mpp_dec_cfg_test: mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mpp_dec_cfg_test"
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpp_dec_cfg_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/build: mpp/base/test/mpp_dec_cfg_test
.PHONY : mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/build

mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/clean:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test && $(CMAKE_COMMAND) -P CMakeFiles/mpp_dec_cfg_test.dir/cmake_clean.cmake
.PHONY : mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/clean

mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/depend:
	cd /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/mpp/base/test /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test /home/jhwang/PROJECT/Netgeer/mine/rockchip_app/mpp/temp/mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mpp/base/test/CMakeFiles/mpp_dec_cfg_test.dir/depend

