
LOCAL_PATH:= $(call my-dir)



# include $(CLEAR_VARS)

# LOCAL_PREBUILT_LIBS := libeventreceiver

# include $(BUILD_MUTI_PREBUILT)


#========================================

# include $(CLEAR_VARS)

# LOCAL_MODULE_TAGS := optional

# LOCAL_MODULE := libeventreceiver

# LOCAL_SRC_FILES := \
#         ./jni/EventReceiver.cpp \


# LOCAL_C_INCLUDES := \
#     $(LOCAL_PATH)/jni/include \
#     system/core/include/utils \
#     system/core/include \
#     frameworks/native/include/android \
#     frameworks/native/include \
#     system/core/libutils \
#     frameworks/base/core/jni


# LOCAL_SHARED_LIBRARIES := \
#         liblog \
# 		libcutils \
# 		libutils  \
# 		libtimer  \
#         libbinder \
#         libeventcontroller \
#         libandroid_runtime

# # include $(BUILD_SHARED_LIBRARY)
# include $(BUILD_STATIC_LIBRARY)

#=================================================================
include $(CLEAR_VARS)


LOCAL_MODULE_PATH := $(PRODUCT_OUT)/system/priv-app
    
DISABLE_DEXPREOPT := true

# LOCAL_STATIC_LIBRARIES := android-support-v4 android-support-v7-appcompat

LOCAL_PACKAGE_NAME := EventReceiverAPK

LOCAL_RESOURCE_DIR := $(LOCAL_PATH)/res 

LOCAL_PRIVILEGED_MODULE := true
# LOCAL_JNI_SHARED_LIBRARIES := true

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, java)

# LOCAL_MODULE := JEventReceiver

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/jni/include \
    system/core/include/utils \
    system/core/include \
    system/core/libutils \
    frameworks/native/include/android \
    frameworks/base/core/jni

LOCAL_SHARED_LIBRARIES := \
        libcutils \
        libutils \
        libbinder \
        libeventcontroller \
        libeventreceiver

# LOCAL_STATIC_LIBRARIES := \
#         libeventreceiver \

# LOCAL_JNI_SHARED_LIBRARIES := libeventreceiver \
#         libeventcontroller


LOCAL_CERTIFICATE := platform

include $(BUILD_PACKAGE)
# include $(BUILD_JAVA_LIBRARY)
# include $(BUILD_STATIC_JAVA_LIBRARY)

include $(LOCAL_PATH)/jni/Android.mk
include $(call all-makefiles-under, $(LOCAL_PATH))


#==================================================





