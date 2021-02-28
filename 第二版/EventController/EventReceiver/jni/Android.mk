####################################################################################
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := libeventreceiver

LOCAL_SRC_FILES := \
        com_tecinno_EventReceiver.cpp \


LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    system/core/include/utils \
    system/core/include \
    frameworks/native/include/android \
    frameworks/native/include \
    system/core/libutils \
    frameworks/base/core/jni


LOCAL_SHARED_LIBRARIES := \
        liblog \
        libcutils \
        libutils  \
        libbinder \
        libandroid_runtime

LOCAL_STATIC_LIBRARIES := \
        libeventcontroller

# include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
####################################################################################




