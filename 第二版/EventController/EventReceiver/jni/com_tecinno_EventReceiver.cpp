
#include <jni.h>
#include <string>
#include <dlfcn.h>
#include "EventControllerService.h"
#include <syslog.h>
#include "android/log.h"
#include "android_runtime/AndroidRuntime.h"
// #include "android_os_Parcel.h"
#include <binder/Parcel.h>
#include "android_os_Parcel.h"
#include "EventControllerClient.h"
#include "EventController.h"

#define EN_OK 0;
#define EN_NG -1;
#define RECEIVER "jp/pioneer/ceam/util/EventReceiver"// jp.pioneer.ceam.util
#define ANDORID_LOG_ERROR 6
#define TAG "EventReceiver"
#define printf(...) __android_log_print(ANDORID_LOG_ERROR, TAG, __VA_ARGS__)

namespace android{


struct fields_t {
    // jfieldID context;
    jmethodID post;
};

static fields_t mfield;

// static jobject mObject;

class MEventClient: public EventControllerClient
{
public:
    MEventClient(JNIEnv* env, jclass clazz, jobject weak_thiz);
    ~MEventClient();
    virtual void notify(int msg, int ext1, int ext2, const Parcel *obj = NULL);
    std::vector<int32_t> val;
private:
    MEventClient();
    jclass      mClass;    //保存类名
    jobject     mObject;   //保存对象引用

};


extern "C" JNIEXPORT jint JNICALL
Java_jp_pioneer_ceam_util_EventReceiver_test(JNIEnv *env, jclass /* this */) {
// Java_com_tecinno_EventReceiver_test(JNIEnv *env, jclass /* this */) {
    printf("Java_com_tecinno_EventReceiver_test");
//    int* out;
//    JNIEnv *env1 = get_env(out);
    //获取保存的Java静态函数id，调用Java静态函数。
    jclass clazz = env->FindClass("com/tecinno/EventReceiver");
    printf("CallStaticVoidMethod : %ld", clazz);
    if (mfield.post == NULL) {
        printf("mfield.post is NULL");
        return EN_NG;
    }
    printf("mfield.post : %d",mfield.post);
    // env->CallStaticVoidMethod(clazz, mfield.post, mObject, 0);
    return EN_OK;
}

extern "C"
JNIEXPORT jint JNICALL
// Java_com_tecinno_EventReceiver_registToService(JNIEnv *env, jclass clazz, jobject weak_this, jintArray ov) {
Java_jp_pioneer_ceam_util_EventReceiver_registToService(JNIEnv *env, jclass clazz, jobject weak_this, jintArray ov) {
    printf("Java_com_tecinno_EventReceiver_registToService");
    // TODO: implement setup()
    //保存Java的类的对象引用
    if (weak_this != NULL) {
        // create new listener and give it to MediaPlayer
        sp<MEventClient> client = new MEventClient(env, clazz, weak_this);
        sp<EventController> mController = EventController::getInstance();
        if (mController != NULL) {
            jint* cv = env->GetIntArrayElements(ov, 0);
            for(int i = 0; i < env->GetArrayLength(ov);++i) {
                client->val.push_back(cv[i]);
            }
            mController->regist(getpid(), client, client->val);
        }
        // mObject = env->NewGlobalRef(weak_this);
        return EN_OK;
    } else {
        return EN_NG;
    }

}

extern "C"
JNIEXPORT jint JNICALL
// Java_com_tecinno_EventReceiver_nativeInit(JNIEnv *env, jclass claz) {
Java_jp_pioneer_ceam_util_EventReceiver_nativeInit(JNIEnv *env, jclass claz) {
    printf("Java_com_tecinno_EventReceiver_nativeInit");
    // TODO: implement nativeInit()
//    jclass clazz = env->FindClass("com/tecinno/EventReceiver");//找到对应的
//    if( clazz == NULL) {
//        printf("clazz  com/tecinno/EventReceiver is NULL, claz: %d, clazz: %d", claz, clazz);
//        return EN_NG;
//    }
    
    // printf("claz: %d, clazz: %d", claz, clazz);
    jclass mclazz = env->FindClass(RECEIVER);
    // mfield.post = env->GetStaticMethodID(clazz, "post", "()V");
    mfield.post = env->GetStaticMethodID(mclazz, "postEvent", "(Ljava/lang/Object;IIILjava/lang/Object;)V");//获取方法 "(Ljava/lang/Object;I)V"); "(Ljava/lang/Object;IIILjava/lang/Object;)V");
    if (mfield.post == NULL) {
        return EN_NG;
    }
    printf("mfield.post : %d", mfield.post);
    return EN_OK;
}extern "C"
JNIEXPORT jint JNICALL
// Java_com_tecinno_EventReceiver_getEventStatus(JNIEnv *env, jclass clazz, jint code) {
Java_jp_pioneer_ceam_util_EventReceiver_getEventStatus(JNIEnv *env, jclass clazz, jint code) {
    // TODO: implement getEventStatus()
    sp<EventController> mController = EventController::getInstance();
    jint status = -1;
    if (mController != NULL) {
        mController->getEventState(code, status);
    }
    printf("Java_com_tecinno_EventReceiver_getEventStatus code %d, status %d", code, status);
    return status;
}


MEventClient::MEventClient(JNIEnv* env, jclass clazz, jobject weak_thiz){

    // jclass clazz = env->GetObjectClass(thiz);

    if (clazz == NULL) {
        printf("Can't find com/tecinno/EventReceiver");
        // jniThrowException(env, "java/lang/Exception", NULL);
        return;
    }

    mClass = (jclass)env->NewGlobalRef(clazz);
    mObject  = env->NewGlobalRef(weak_thiz);
}

MEventClient::~MEventClient(){
    JNIEnv *env = AndroidRuntime::getJNIEnv();
    env->DeleteGlobalRef(mObject);
    env->DeleteGlobalRef(mClass);
}

/*
    更新消息到Java层EventReceiver,通过保存在client中的Java对象引用，调用Java静态函数postEvent


*/
void MEventClient::notify(int msg, int ext1, int ext2, const Parcel *obj) {
    printf("MEventClient::notify: msg:%d arg1:%d",msg,ext1);
    JNIEnv *env = AndroidRuntime::getJNIEnv();

    if (obj && obj->dataSize() > 0) {
        jobject jParcel = createJavaParcelObject(env);
        if (jParcel != NULL) {
            Parcel* nativeParcel = parcelForJavaObject(env, jParcel);
            if(nativeParcel != NULL) {
                nativeParcel->setData(obj->data(), obj->dataSize());
            }   
            env->CallStaticVoidMethod(mClass, mfield.post, mObject,
                                      msg, ext1, ext2, jParcel);
            env->DeleteLocalRef(jParcel);
        }
        printf("JNIMiscClientListener::notify  obj && obj->dataSize() ");
    } else {
        env->CallStaticVoidMethod(mClass, mfield.post, mObject,
                                  msg, ext1, ext2, NULL);
        printf("JNIMiscClientListener::notify  else");
    }
}

};