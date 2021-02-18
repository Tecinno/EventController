/*
* (c) PIONEER CORPORATION 2014
* 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
* All Rights Reserved.
*/

#ifndef PIONEER_IEVENTCONTROLLERSERVICE_H
#define PIONEER_IEVENTCONTROLLERSERVICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/threads.h>
#include <stdio.h>
#include <list>
#include <vector>
#include "NEventInfoData.h"
#include <binder/IServiceManager.h>
#include <IEventControllerClient.h>

#define ERROR_APPEAR 1
#define NO_ERROR 0

#define TECINNO_EVENTCONTROLLER_SERVIE (String16("EventControllerService"))

namespace android
{

class IEventControllerService: public IInterface
{
public:
    DECLARE_META_INTERFACE( EventControllerService );

    virtual status_t regist(pid_t pid, const sp<IEventControllerClient>& c, const std::vector<int32_t>& val) = 0;
    virtual status_t getEvetnState(int32_t code, int &status) = 0;
};

class BnEventControllerService: public BnInterface<IEventControllerService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}; // namespace android

#endif //PIONEER_IMISCMANAGERSERVICE_H


