# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

if (NOT CMAKE_TOOLCHAIN_FILE)
    set (BUILDROOT_DIR "../buildroot")
    set (CMAKE_TOOLCHAIN_FILE ${BUILDROOT_DIR}/output/host/usr/share/buildroot/toolchainfile.cmake)
endif()

message(STATUS "cmake toolchain path ${CMAKE_TOOLCHAIN_FILE}")

project(rkPlayer CXX)
################################################
# include all check files
################################################
include (CheckIncludeFiles)
include (CheckFunctionExists)
include (CheckSymbolExists)
include (CheckLibraryExists)
include (CheckStructHasMember)
include (CheckTypeSize)

################################################
# append cmake_module_path
################################################
#list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

################################################
# option
################################################
option (OPTION_PTHREADS "Enable support for threads" ON)

################################################
# set property to classify library kinds
################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

################################################
# System architecture detection
################################################
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYSPROC)
set(X86_ALIASES x86 i386 i686 x86_64 amd64)
list(FIND X86_ALIASES "${SYSPROC}" X86MATCH)
if("${CMAKE_C_COMPILER}" MATCHES "-buildroot-[^/]+$")
    message(STATUS "Detected Buildroot toolchain")
    # Use buildroot toolchain's default architecture settings
elseif("${SYSPROC}" STREQUAL "" OR X86MATCH GREATER "-1")
    message(STATUS "Detected x86 system processor")
    set(X86 true)
    add_definitions(-DARCH_X86=1)
    if("${CMAKE_SIZEOF_VOID_P}" MATCHES 8)
        set(X64 true)
        add_definitions(-DARCH_X64=1)
        message(STATUS "Define X86_64 to 1")
    endif()
elseif(${SYSPROC} STREQUAL "armv6l")
    message(STATUS "Detected ARMv6 system processor")
    set(ARM true)
    set(ARMEABI_V6 true)
elseif(${SYSPROC} STREQUAL "armv7-a")
    message(STATUS "Detected ARMv7 system processor")
    set(ARM true)
    set(ARMEABI_V7A true)
elseif(${SYSPROC} STREQUAL "armv7-a_hardfp" OR ${SYSPROC} STREQUAL "armv7l")
    message(STATUS "Detected ARMv7 system processor")
    set(ARM true)
    set(ARMEABI_V7A_HARDFP true)
elseif(${SYSPROC} STREQUAL "aarch64" OR ${SYSPROC} STREQUAL "armv8-a")
    message(STATUS "Detected ARMv8 system processor")
    set(ARM true)
    set(ARMEABI_V8 true)
else()
    message(STATUS "CMAKE_SYSTEM_PROCESSOR value `${CMAKE_SYSTEM_PROCESSOR}` is unknown")
    message(STATUS "Please add this value near ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}")
endif()

if(UNIX)
    SET(PLATFORM_LIBS pthread)
    if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(PLATFORM_LIBS ${PLATFORM_LIBS} rt)
    endif()
endif(UNIX)

################################################
# Compiler detection
################################################
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CLANG true)
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(INTEL_CXX true)
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC true)
endif()

if(INTEL_CXX AND UNIX)
    # treat icpc roughly like gcc
    set(GCC true)
    add_definitions(-Wall -Wextra -Wshadow)
elseif(CLANG)
    # treat clang roughly like gcc
    set(GCC true)
    add_definitions(-Wall -Wextra -Wshadow -ffast-math)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -Wextra -Wshadow -ffast-math)
    if (GCC_HAS_STACK_REALIGN)
        add_definitions(-mstackrealign)
    endif()
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
endif()

if(GCC)
    if(ARM)
        if(ARMEABI_V6)
            add_definitions(-march=armv6 -mfloat-abi=hard -mfpu=vfp)
        elseif(ARMEABI_V7A)
            add_definitions(-march=armv7-a -mfloat-abi=softfp -mfpu=neon)
        elseif(ARMEABI_V7A_HARDFP)
            add_definitions(-march=armv7-a -mfloat-abi=hard -mfpu=neon)
        elseif(ARMEABI_V8)
            add_definitions(-march=armv8-a)
        endif()
    else()
        if(X86 AND NOT X64)
            add_definitions(-march=i686)
        endif()
    endif()

    if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
        add_definitions(-g)
    endif()

    # disable multichar warning
    add_definitions(-Wno-multichar)
    # add PIC flag
    add_definitions(-fPIC)
    # disable exception for C++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
    # save intermediate files
    # add_definitions(-save-temps)

    # for libary linking
    set(BEGIN_WHOLE_ARCHIVE -Wl,--whole-archive)
    set(END_WHOLE_ARCHIVE -Wl,--no-whole-archive)

    option(ASAN_CHECK "enable Address Sanitizer (Asan)" OFF)
    if(ASAN_CHECK)
        add_definitions(-fsanitize=address -static-libasan -g)
        set(ASAN_LIB libasan.a dl rt m)
        set(ASAN_BIN dl rt m)
    endif(ASAN_CHECK)

endif(GCC)

################################################
# configure file
################################################
# ----------------------------------------------------------------------------
# Package check
# ----------------------------------------------------------------------------
#find_package(PkgConfig)
#INCLUDE(GNUInstallDirs)
#pkg_search_module(PTHREAD pthread)

# ----------------------------------------------------------------------------
#  Include path
# ----------------------------------------------------------------------------
# project overall include path
set(SRC_TOP ${PROJECT_SOURCE_DIR}/src)
include_directories(${SRC_TOP})
include_directories(${SRC_TOP}/rkdrm)
include_directories(${SRC_TOP}/rkrga)

# ----------------------------------------------------------------------------
#  library path
# ----------------------------------------------------------------------------
# project overall library path
link_directories(CMAKE_SYSROOT/usr/lib)

################################################
#  set project install path
################################################
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "install prefix" FORCE)
#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(SRC_TOP ${PROJECT_SOURCE_DIR}/src)
# Source files for both the shared and static libraries
set(MEDIAPLAYER_SOURCES
	${SRC_TOP}/mediaPlayer.cpp 
	${SRC_TOP}/packet_queue.cpp
	${SRC_TOP}/system_time.cpp
	${SRC_TOP}/thread_wrapper.cpp
	${SRC_TOP}/rkdrm/dev.cpp
	${SRC_TOP}/rkdrm/modeset.cpp
	${SRC_TOP}/rkdrm/bo.cpp
	${SRC_TOP}/media_time_impl.cpp
	${SRC_TOP}/media_util.cpp
	${SRC_TOP}/mpp_video_frame_thread_safe.cpp
	${SRC_TOP}/egl_display.cpp
	${SRC_TOP}/xdg-shell-protocol.cpp
	${SRC_TOP}/main.cpp)

# Define the sysrootfs path if it's set, or use an empty string if not.
if(CMAKE_TOOLCHAIN_FILE)
    # Case 1: Sysrootfs is defined
    message(STATUS "Using sysroot: ${CMAKE_TOOLCHAIN_FILE}")
    #include_directories(${SYSROOTFS}/include)

	set(COMMON_INCSDIR
		${CMAKE_SYSROOT}/usr/include
		${CMAKE_SYSROOT}/usr/include/drm
	)

	set(COMMON_LIBSDIR
		${CMAKE_SYSROOT}/usr/lib)

	set(WAYLAND_INCSDIR
		${COMMON_INCSDIR}/drm
	)
else()
endif()

# use sys rootfs
set(WAYLAND_LIBS
    drm
    mali
    wayland-client
    wayland-cursor
    wayland-egl
    wayland-server)

# use sys rootfs
set(FFMPEG_LIBS 
	ssl
	crypto
    avcodec
    avutil
    avformat)

# use sys rootfs or current
set(RKMPP_LIBS
    rockchip_mpp)

set(COMMON_LIBS
 pthread
 rt
 m
)

set(LIB_CFLAGS
 -g
 -Wall
)

# you can use just rockchip_mpp.so of sysrootfs instead of this.
add_subdirectory(mpp)

# Add the executable test application
add_executable(rkplayer ${MEDIAPLAYER_SOURCES})

# Include directories for the test application
target_include_directories(rkplayer PUBLIC ${COMMON_INCSDIR} ${WAYLAND_INCSDIR} ${MPP_INCS})
target_compile_options(rkplayer PRIVATE ${LIB_CFLAGS} -fPIC )

# Link the test application with the shared library and the prebuilt static library
target_link_libraries(rkplayer PRIVATE 
	${COMMON_LIBS} 
	${WAYLAND_LIBS}
	${FFMPEG_LIBS}
	${RKMPP_LIBS})

