/*
* (c) PIONEER CORPORATION 2014
* 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
* All Rights Reserved.
*/

#ifndef TECINNO_MISCMANAGERCLIENT_H
#define TECINNO_MISCMANAGERCLIENT_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/threads.h>
#include "jni.h"

#include "IEventControllerClient.h"
#include "IEventControllerService.h"
#include "EventController.h"

namespace android
{

struct fields {
    jfieldID context;
    jmethodID notify;
    jmethodID post;
};

class EventControllerClient : public BnEventControllerClient
{
public:
    EventControllerClient();
    ~EventControllerClient();
    virtual void notify(int msg, int ext1, int ext2, const Parcel *obj);
    // virtual status_t getEventState(int32_t code, int32_t& data);

private:
    void connect();
    void disconnect();

private:
    // sp<IEventControllerService> mManagerService;
    sp<EventController> mController;
    // jobject mEventReceiver;
    // Mutex mLock;
    // fields mfields;
};

};
#endif //PIONEER_MISCMANAGERCLIENT_H

