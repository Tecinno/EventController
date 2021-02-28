#ifndef TECINNO_EVENTCONTROLLER_H
#define TECINNO_EVENTCONTROLLER_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/threads.h>
#include "jni.h"
#include "IEventControllerClient.h"
#include "IEventControllerService.h"

namespace android
{
    class EventController: public RefBase
    {
    private:
        /* data */
    public:
        EventController(/* args */);
        ~EventController();
        static sp<EventController> getInstance();
        status_t getEventState(int32_t code, int32_t& data);
        status_t regist(pid_t pid, const sp<IEventControllerClient>& c, std::vector<int32_t>& val);
        

    private:
        sp<IEventControllerService> mService;
        void connect();
        void disconnect();
    public:
        static sp<EventController> mInstance;
    
    };
    
    
    
};

#endif