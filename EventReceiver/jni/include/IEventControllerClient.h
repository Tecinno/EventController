/*
* 
* 
* 
*/

#ifndef PIONEER_IMISCMANAGERCLIENT_H
#define PIONEER_IMISCMANAGERCLIENT_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/Log.h>


namespace android
{

class IEventControllerClient: public IInterface
{
public:
    DECLARE_META_INTERFACE(EventControllerClient);

    virtual void notify(int id, int msg1, int msg2, const Parcel *parcel) = 0;
};

// ----------------------------------------------------------------------------

class BnEventControllerClient: public BnInterface<IEventControllerClient>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}; // namespace android

#endif // PIONEER_IMISCMANAGERCLIENT_H

