// Script registrar source ownership: CD2 initializer 0x82FDFC08 names cDynamicBody,
// and cleanup 0x830403C0 destroys the same descriptor. Shared interface names are ours.

#include "PHYSICS/cDynamicBody.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace PHYSICS
{
    bool cDynamicBody::RetIsOnFire() const
    {
        return IsOnFire();
    }

    // The registered-class getter's descriptor is cNetDynamicBody's, and its
    // table at 0x82132398 is installed by that class's constructor.
    const Fun_Runtime::cClass &cNetDynamicBody::RetClass() const
    {
        return *ms_pcNetDynamicBodyClass;
    }

    bool cNetDynamicBody::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcNetDynamicBodyClass->IsA(c);
    }

    static Fun_Runtime::cScriptTypeRegistrar<cDynamicBody> cDynamicBodyScriptRegistrar(
        "cDynamicBody", "cBody");

    Fun_Runtime::cClass &cDynamicBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x645, "cDynamicBody", 0x420);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cDynamicBody::ms_pcDynamicBodyClass = &cDynamicBody::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cDynamicBodyRegistrar(
        "cDynamicBody", cDynamicBody::MakeNew, 0x420, false);

    static GOM::cProtoRegistrar cDynamicBodySpawningRegistrar(
        cDynamicBody::StaticCreateClass(), cDynamicBody::SpawnFromPrototype);

    const Fun_Runtime::cClass &cDynamicBody::RetClass() const
    {
        return *ms_pcDynamicBodyClass;
    }

    bool cDynamicBody::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcDynamicBodyClass->IsA(c);
    }

    RWS::CAttributeHandler *cDynamicBody::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cDynamicBodyPrototype(packet);
    }

    RWS::CAttributeHandler *cDynamicBody::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cDynamicBody;
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDynamicBody::RetScriptTypeRegistration() const
    {
        return &cDynamicBodyScriptRegistrar;
    }
}
