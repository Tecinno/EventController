
#define LOG_TAG "EventController"
#include <binder/IServiceManager.h>
#include "EventControllerClient.h"

#define	 EN_RET_OK 0
#define  EN_RET_NG 1

namespace android
{



EventControllerClient::EventControllerClient()
{
    connect();
    LOGD("EventControllerClient initialization");
}

EventControllerClient::~EventControllerClient()
{
    disconnect();
    LOGD("EventControllerClient finalization");
}


void EventControllerClient::notify(int msg, int ext1, int ext2, const Parcel *obj)
{
    LOGD("EventControllerClient::notify");

}

void EventControllerClient::connect()
{
    LOGD("EventControllerClient::connect");

    if(mController == NULL)
    {
        mController = EventController::getInstance();
        if (mController == NULL) {
            LOGE("EventController.getInstance is NULL");
            return;
        }
    }
}

void EventControllerClient::disconnect()
{
    LOGD("EventControllerClient::disconnect");

    if(mController != NULL)
    {
        mController = NULL;
    }
}

};

