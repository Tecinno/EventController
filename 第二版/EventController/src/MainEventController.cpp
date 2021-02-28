/*
* Copyright @ 2013 Pioneer Suntec Electronic Technology Co.,LTD (PSET)
* All Rights Reserved.
* Created on: 2013-02-28
*/
#define LOG_TAG "EventController"


#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include "EventControllerService.h"


using namespace android;

int main(int argc __unused, char** argv __unused)
{
    LOGE("MainEventController");
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();

    sp<EventControllerService> eMgr = new EventControllerService();
    defaultServiceManager()->addService(TECINNO_EVENTCONTROLLER_SERVIE, eMgr);

    //set the oom adj value
    // setOomAdj(PIONEER_SERVICE_ID_MISCMGR,PIONNER_SERVICES_STS_BACKGROUND_RUN);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}

