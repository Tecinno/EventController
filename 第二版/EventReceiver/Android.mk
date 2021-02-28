
LOCAL_PATH:= $(call my-dir)

#=================================================================
include $(CLEAR_VARS)


LOCAL_MODULE_PATH := $(PRODUCT_OUT)/system/priv-app
    
DISABLE_DEXPREOPT := true

# LOCAL_STATIC_LIBRARIES := android-support-v4 android-support-v7-appcompat

LOCAL_PACKAGE_NAME := EventReceiverAPK

LOCAL_RESOURCE_DIR := $(LOCAL_PATH)/res 

# LOCAL_PRIVILEGED_MODULE := true
# LOCAL_JNI_SHARED_LIBRARIES := true

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := jeventreceiver

LOCAL_SRC_FILES := $(call all-java-files-under, java)

# LOCAL_C_INCLUDES := \
#     $(LOCAL_PATH)/jni/include \
#     system/core/include/utils \
#     system/core/include \
#     system/core/libutils \
#     frameworks/native/include/android \
#     frameworks/base/core/jni

# LOCAL_SHARED_LIBRARIES := \
#         libcutils \
#         libutils \
#         libbinder \
#         libeventcontroller \
#         libeventreceiver

# LOCAL_SHARED_LIBRARIES := jeventreceiver

# LOCAL_AAPT_FLAGS := --auto-add-overlay \
#                 --extra-packages com.tecinno.receiver \



# LOCAL_JNI_SHARED_LIBRARIES := libeventreceiver \
#         libeventcontroller


LOCAL_CERTIFICATE := platform

include $(BUILD_PACKAGE)
# include $(BUILD_JAVA_LIBRARY)
# include $(BUILD_STATIC_JAVA_LIBRARY)

include $(call all-makefiles-under, $(LOCAL_PATH))


#==================================================





