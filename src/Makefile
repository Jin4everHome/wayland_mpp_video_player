#
# EGL/GLES MPP video player
#

# don't change this line
SELF_PATH := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
include $(SELF_PATH)/../../build/rk-hal-common.mk

SRC_TOP                       = $(SELF_PATH)
LOCAL_CFLAGS                  = $(DEFAUL_USER_BUILD_CFLAGS) $(CFLAGS)
LOCAL_LDFLAGS                 = -lpthread -lm -lrt
LOCAL_CC                      = $(TARGET_CROSS)gcc
LOCAL_CXX                     = $(TARGET_CROSS)g++
LOCAL_C_INCLUDES              = $(GLOBAL_USER_C_INCLUDES)
LOCAL_SHARED_SEARCH_PATH      = $(GLOBAL_USER_LIB_SEARCH_PATH)


TARGET_NAME = media_player
TARGET = $(SRC_TOP)/$(TARGET_NAME)

SOURCES = \
	$(SRC_TOP)/mediaPlayer.cpp  \
	$(SRC_TOP)/packet_queue.cpp \
	$(SRC_TOP)/system_time.cpp \
	$(SRC_TOP)/thread_wrapper.cpp \
	$(SRC_TOP)/rkdrm/dev.cpp  \
	$(SRC_TOP)/rkdrm/modeset.cpp  \
	$(SRC_TOP)/rkdrm/bo.cpp  \
	$(SRC_TOP)/media_time_impl.cpp \
	$(SRC_TOP)/media_util.cpp \
	$(SRC_TOP)/mpp_video_frame_thread_safe.cpp \
	$(SRC_TOP)/egl_display.cpp \
	$(SRC_TOP)/xdg-shell-protocol.cpp \
	$(SRC_TOP)/main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

LOCAL_C_INCLUDES += \
	$(SRC_TOP) \
	$(SRC_TOP)/rkdrm \
	$(GLOBAL_USER_C_INCLUDES)/drm \

LOCAL_SHARED_SEARCH_PATH += \
	$(SRC_TOP) \

LOCAL_CFLAGS += \
	$(addprefix -I, $(LOCAL_C_INCLUDES))

LOCAL_CFLAGS += \

LOCAL_LDFLAGS += -lavcodec -lavformat -lavutil -lrga -lrockchip_mpp -ldrm -lwayland-egl -lwayland-client -lwayland-server -lwayland-cursor -lmali

LOCAL_LDFLAGS += \
	$(addprefix -L, $(LOCAL_SHARED_SEARCH_PATH))

all: $(TARGET)
$(TARGET): $(OBJECTS)
	@echo "[LINK]" $(call pathstrip, $@, $(SRC_TOP))
	@$(LOCAL_CXX) $^ $(LOCAL_LDFLAGS) -o $(TARGET)

%.o: %.cpp
	@echo "[CXX]" $(call pathstrip, $@, $(SRC_TOP))
	@$(LOCAL_CXX) $(LOCAL_CFLAGS) $< -o $@

clean:
	@echo "[Clean]"
	@find $(SRC_TOP) -name "*.o" -exec rm {} \;
	@rm -f $(TARGET)

install:
	@echo "[Install]"
ifneq ($(INSTALL_TARGET_PATH),)
	@install -m 755 $(TARGET) $(INSTALL_TARGET_PATH)/usr/bin
else
	@echo "...skip"
endif
