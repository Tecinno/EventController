/*
 * (c) PIONEER CORPORATION 2014
 * 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
 * All Rights Reserved.
 */

#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <utils/Errors.h>  // for status_t
#include "IEventControllerService.h"

namespace android
{

enum {
    GET_EVENT_STATE = IBinder::FIRST_CALL_TRANSACTION,
    REGIST
};

class BpEventControllerService: public BpInterface<IEventControllerService>
{
public:
    BpEventControllerService(const sp<IBinder>& impl)
        : BpInterface<IEventControllerService>( impl ) {
    }

    status_t getEventState(int32_t code,int32_t &status) {
        Parcel data, reply;
        data.writeInterfaceToken(IEventControllerService::getInterfaceDescriptor());
        data.writeInt32(code);
        remote()->transact(GET_EVENT_STATE, data, &reply);
        status = reply.readInt32();
        return reply.readInt32();
    }
    status_t regist(pid_t pid, const sp<IEventControllerClient>& c, const std::vector<int32_t>& val) {
        Parcel data, reply;
        data.writeInterfaceToken(IEventControllerService::getInterfaceDescriptor());
        data.writeInt32(pid);
        data.writeStrongBinder(c->asBinder());
        data.writeInt32Vector(val);  //writeInt32Vector(const std::vector<int32_t>& val);
        remote()->transact(REGIST, data, &reply);
        return reply.readInt32();
        // return interface_cast<IMiscManager>( reply.readStrongBinder() );
    }
};

IMPLEMENT_META_INTERFACE( EventControllerService, "com.tecinno.IEventControllerService" );

// ----------------------------------------------------------------------

status_t BnEventControllerService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags )
{
    switch( code ) {
    case GET_EVENT_STATE: {
        CHECK_INTERFACE(IEventControllerService, data, reply);
        int status = 0;
        int code = data.readInt32();
        int ret = getEventState(code, status);
        reply->writeInt32(status);
        reply->writeInt32(ret);
        return NO_ERROR;
    }
    break;
    case REGIST: {
        CHECK_INTERFACE(IEventControllerService, data, reply);
        pid_t pid = data.readInt32();
        sp<IEventControllerClient> client = interface_cast<IEventControllerClient>(data.readStrongBinder());
        std::vector<int32_t> val;
        data.readInt32Vector(&val);
        int ret = regist(pid, client, val);
        reply->writeInt32(ret);
        return NO_ERROR;
    }
    break;
    default:
        return BBinder::onTransact( code, data, reply, flags );
    };
}

// ----------------------------------------------------------------------------

}; // namespace android

