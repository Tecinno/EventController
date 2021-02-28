LOCAL_PATH:= $(call my-dir)

####################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := libeventcontroller

LOCAL_SRC_FILES := \
        IEventControllerClient.cpp \
        IEventControllerService.cpp \
        EventControllerClient.cpp \
        EventController.cpp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../include \
    system/core/include/utils \
    system/core/include \
    frameworks/native/include/android \
    frameworks/native/include \
    system/core/libutils \


LOCAL_SHARED_LIBRARIES := \
        liblog \
		libcutils \
		libutils  \
        libbinder

include $(BUILD_STATIC_LIBRARY)


include $(call all-makefiles-under,$(LOCAL_PATH))
####################################################################################
