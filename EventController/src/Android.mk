LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MainEventController.cpp \
    EventControllerService.cpp \

LOCAL_MODULE:= eventcontrollerservice
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../include \
    system/core/include/utils \
    system/core/include \
    frameworks/native/include/android \
    system/core/libutils \

LOCAL_SHARED_LIBRARIES := \
        libcutils \
        libutils \
        libbinder \
        libeventcontroller

LOCAL_INIT_RC := eventcontroller.rc

include $(BUILD_EXECUTABLE)
