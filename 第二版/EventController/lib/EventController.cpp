#define LOG_TAG "EventController"

#include "EventController.h"

android::Mutex inst("EVENT_CONTROLLER_ARTWORK_LOCK");

namespace android
{
    sp<EventController> EventController::mInstance = NULL;

    EventController::EventController() {
        LOGD("EventController::EventController");
        connect();
    }

    EventController::~EventController() {
        LOGD("EventController::~EventController");
        disconnect();
    }

    sp<EventController> EventController::getInstance() {
        if(mInstance.get() != NULL){
            return mInstance;
        }
        android::AutoMutex _l(inst);
        if(mInstance.get() == NULL) {
            mInstance = new EventController();
        }
        return mInstance;
    }

    void EventController::connect()
    {
        LOGD("EventController::connect");

        if(mService == NULL)
        {
            sp<IServiceManager> sm = defaultServiceManager();
            LOGD("EventController::defaultServiceManagers");
            mService = IEventControllerService::asInterface(sm->getService(TECINNO_EVENTCONTROLLER_SERVIE));
            
            int i = 5;
            while(mService == NULL && i--)
            {
                LOGE("mService is NULL , try"); 
                mService = IEventControllerService::asInterface(sm->getService(TECINNO_EVENTCONTROLLER_SERVIE));
            }
        }
    }

    void EventController::disconnect()
    {
        LOGD("EventController::disconnect");

        if(mService != NULL)
        {
            mService = NULL;
        }
    }

    status_t EventController::getEventState(int32_t code, int32_t& status) {
        if(mService != NULL)
        {
            return mService->getEventState(code, status);
        } else {
            LOGE("EventController::getEventState mService is NULL");
            connect();
            if(mService != NULL)
            {   
                return mService->getEventState(code, status);
            } else {
                LOGE("EventController::getEventState mService is NULL");
            }
        }
        LOGE("EventController::getEventState mService is NULL");
        return ERROR_APPEAR;
    }

    status_t EventController::regist(pid_t pid, const sp<IEventControllerClient>& c, std::vector<int32_t>& val) {
        if(mService != NULL)
        {   
            return mService->regist(pid, c, val);
        } else {
            LOGE("EventController::regist mService is NULL");
            connect();
            if(mService != NULL)
            {   
                return mService->regist(pid, c, val);
            } else {
                LOGE("EventController::regist mService is NULL");
            }
        }
        
        return ERROR_APPEAR;
    }

};