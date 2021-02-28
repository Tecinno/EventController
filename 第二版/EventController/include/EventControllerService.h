/*
* (c) PIONEER CORPORATION 2014
* 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
* All Rights Reserved.
*/

#ifndef TECINNO_EVENTCONTROLLERSERVICE_H
#define TECINNO_EVENTCONTROLLERSERVICE_H


// #include <utils/String8.h>
// #include <cutils/atomic.h>
// #include <binder/Parcel.h>
// #include <utils/Vector.h>

#include "IEventControllerService.h"



namespace android
{

struct ClientEntry {
    pid_t pid;
    sp<IEventControllerClient> client;
    std::vector<int32_t> val;
};

class EventControllerService : public BnEventControllerService
{
public:
    EventControllerService();
    virtual	~EventControllerService();
    status_t regist(pid_t pid, const sp<IEventControllerClient>& c, const std::vector<int32_t>& val);
    status_t getEventState(int32_t code, int32_t &data);
    status_t notify(int32_t id, int32_t msg1, int32_t msg2, const Parcel *parcel);
    status_t getEventAStatus(int32_t code, int32_t &data);
    status_t getEventBStatus(int32_t code, int32_t &data);
private:
    // void clearDeathClient();

protected:

private:
    Mutex mLock;
    // SortedVector< > mcs;
    std::list< ClientEntry* > mClients;
    Mutex mVectorLock;
    std::vector < std::list <ClientEntry*> > mClientNotify;
};

}; // namespace android

#endif // PIONEER_MISCMANAGER_H


