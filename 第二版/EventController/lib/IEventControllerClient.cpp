/*
* (c) PIONEER CORPORATION 2014
* 25-1 Nishi-machi Yamada Kawagoe-shi Saitama-ken 350-8555 Japan
* All Rights Reserved.
*/

#define LOG_TAG "EventController"

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <IEventControllerClient.h>

namespace android
{

enum {
    NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
};

class BpEventControllerClient: public BpInterface<IEventControllerClient>
{
public:
    BpEventControllerClient(const sp<IBinder>& impl)
        : BpInterface<IEventControllerClient>(impl) {
    }

    virtual void notify(int msg, int ext1, int ext2, const Parcel *obj) {
        Parcel data, reply;
        data.writeInterfaceToken(IEventControllerClient::getInterfaceDescriptor());
        data.writeInt32(msg);
        data.writeInt32(ext1);
        data.writeInt32(ext2);

        if (obj && obj->dataSize() > 0) {
            data.appendFrom(const_cast<Parcel *>(obj), 0, obj->dataSize());
        }

        LOGD("BpEventControllerClient::NOTIFY");
        remote()->transact(NOTIFY, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(EventControllerClient, "com.tecinno.IEventControllerClient");

// ----------------------------------------------------------------------

status_t BnEventControllerClient::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    LOGD("BnEventControllerClient::onTransact");

    switch(code) {
    case NOTIFY: {
        CHECK_INTERFACE(IMiscManagerClient, data, reply);
        int msg = data.readInt32();
        int ext1 = data.readInt32();
        int ext2 = data.readInt32();
        Parcel obj;

        if (data.dataAvail() > 0) {
            //obj.appendFrom(const_cast<Parcel *>(&data), data.dataPosition(), data.dataAvail());
           // obj.setData(data.data(), data.dataSize());
			obj.appendFrom( const_cast<Parcel *>(&data), data.dataPosition(), data.dataAvail() );
            obj.setDataPosition(0);
        }

        LOGD("BnEventControllerClient::NOTIFY");
        notify(msg, ext1, ext2, &obj);
        return NO_ERROR;
    }
    break;
    default:
        return BBinder::onTransact(code, data, reply, flags);
    }
}

}; // namespace android

