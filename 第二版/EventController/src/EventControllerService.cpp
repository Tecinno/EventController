/*
* (c) PIONEER CORPORATION 2014
* 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
* All Rights Reserved.
*/

#define LOG_TAG "EventController"

#include "EventControllerService.h"

android::Mutex mClientEntrys("CLIENT_ENTRY_ARTWORK_LOCK");

namespace android
{


// Mutex mLock;

EventControllerService::EventControllerService()
: mClients(), mClientNotify(LAST_NOTIFY_EVENT_SIZE)
{
    LOGD("EventControllerService::EventControllerService() construct start");
    AutoMutex _l(mClientEntrys);
    mClients.clear();
}

EventControllerService::~EventControllerService()
{
    LOGD("EventControllerService destruct");

    //释放内存mClients
}

/*
    param:
        pid:每个进程只能注册一个client，否则替换。
        c:客户端需要继承重写的类
        val：客服端重写哪几个接口，需要将接口的ID写入val中。接口ID与EventInfoData.java中的EN_KEY_NOTIFY对应。
*/
status_t EventControllerService::regist(pid_t pid, const sp<IEventControllerClient>& c, const std::vector<int32_t>& val) {
    if (c != NULL) {
        AutoMutex _l(mClientEntrys);
        ClientEntry* entry = new ClientEntry;
        entry->pid = pid;
        entry->client = c;
        entry->val = val;
        //防止重复
        std::list< ClientEntry* >::iterator mc = mClients.begin();
        for(;mc != mClients.end(); ++mc) {
            if ((*mc)->pid == pid) {
                delete (*mc);
                mClients.erase(mc);
            }
        }

        mClients.push_back(entry);

        //把client重写的方法ID记录在mClientNotify中，
        //之后notify可以针对特定的client更新。
        //val中的数字和EN_KEY_NOTIFY中的方法是对应的。
        std::vector<int32_t>::iterator it = entry->val.begin();
        for (; it != entry->val.end(); it++) {
            mClientNotify[*it].push_back(entry);
        }
        return NO_ERROR;
    } else {
        LOGE("EventControllerService::regist client is NULL");
        return ERROR_APPEAR;
    }
    
}

status_t EventControllerService::getEventState(int32_t code, int32_t &status) {
    switch (code)
    {
    case GET_EVENT_A_STATUS:
        /* code */
        LOGD("EventControllerService::getEventState code = %d", code);
        getEventAStatus(code, status);
        break;
    case GET_EVENT_B_STATUS:
        /* code */
        LOGD("EventControllerService::getEventState code = %d", code);
        getEventBStatus(code, status);
        break;
    default:
        LOGD("EventControllerService::getEventState no this code : %d", code);
        return ERROR_APPEAR;
        break;
    }
    return NO_ERROR;
}

status_t EventControllerService::getEventAStatus(int32_t code, int32_t &data) {
    LOGD("EventControllerService::getEvetnAStatus code = %d", code);
    data = code;
    return NO_ERROR;
}

status_t EventControllerService::getEventBStatus(int32_t code, int32_t &data) {
    LOGD("EventControllerService::getEvetnBStatus code = %d", code);
    data = code;
    return NO_ERROR;
}

/*

    param:
        id是和EN_KEY_NOTIFY中的ID匹配的
*/
status_t EventControllerService::notify(int32_t id, int32_t msg1, int32_t msg2, const Parcel *parcel)
{
    LOGD("EventControllerService::notify id = %d", id);

    // Mutex::Autolock _l(mClientEntrys);
    AutoMutex _l(mClientEntrys);
    if (mClients.empty()) {
        LOGE("EventControllerService::notify mClients is NULL");
        return ERROR_APPEAR;
    }
    
    //回调重写过该ID的client。
    std::list<ClientEntry*>::iterator it;
    for (it = mClientNotify[id].begin(); it != mClientNotify[id].end(); it++) {
        if((*it)->client != NULL) {
            (*it)->client->notify(id, msg1, msg2, parcel);
        } else {
            delete (*it);
            mClientNotify[id].erase(it);
        }
    }
    return NO_ERROR;
}

// void EventControllerService::removeClient(wp<IEventControllerClient> client)
// {
//     Mutex::Autolock lock(mVectorLock);
//     mClients.remove(client);
// }

// void EventControllerService::clearDeathClient()
// {
//     Mutex::Autolock _l(mVectorLock);
//     int32_t size = mClients.size();

//     while (size) {
//         wp<Client> wpClient = mClients.itemAt(--size);
//         sp<Client> spClient = wpClient.promote();

//         if(spClient == NULL) {
//             mClients.remove(wpClient);
//         }
//     }
// }

// void EventControllerService::dumpLog()
// {
//     if (mClient == NULL) {
//         LOGE("client error");
//         return;
//     }

//     LOGD("***************************");
//     LOGD("pid=%d,uid=%d,%s", mPid, mUID, mClient->getInterfaceDescriptor().string());
//     LOGD("***************************");

// }
};

