// Script registrar source ownership: CD2 initializer 0x82FDFC08 names cDynamicBody,
// and cleanup 0x830403C0 destroys the same descriptor. Shared interface names are ours.

#include "PHYSICS/cDynamicBody.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

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

    static Fun_Runtime::cScriptTypeRegistrar<cDynamicBody> cDynamicBodyScriptRegistrar(
        "cDynamicBody", "cBody");

    Fun_Runtime::cClass &cDynamicBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x645, "cDynamicBody", 0x420);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cDynamicBody::ms_pcDynamicBodyClass = &cDynamicBody::StaticCreateClass();

    const Fun_Runtime::cClass &cDynamicBody::RetClass() const
    {
        return *ms_pcDynamicBodyClass;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDynamicBody::RetScriptTypeRegistration() const
    {
        return &cDynamicBodyScriptRegistrar;
    }
}
