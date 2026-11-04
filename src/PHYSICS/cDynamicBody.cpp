// Script registrar source ownership: CD2 initializer 0x82FDFC08 names cDynamicBody,
// and cleanup 0x830403C0 destroys the same descriptor. Shared interface names are ours.
#include "PHYSICS/cDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"

namespace PHYSICS
{
    static Fun_Runtime::cScriptTypeRegistrar<cDynamicBody> cDynamicBodyScriptRegistrar(
        "cDynamicBody", "cBody");
}

#include "cd2/memory.h"

namespace PHYSICS
{
    Fun_Runtime::cClass &cDynamicBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x645, "cDynamicBody", 0x420);
        return *descriptor;
    }
}

namespace PHYSICS
{
    const Fun_Runtime::cClass *cDynamicBody::ms_pcDynamicBodyClass = &cDynamicBody::StaticCreateClass();

    const Fun_Runtime::cClass &cDynamicBody::RetClass() const
    {
        return *ms_pcDynamicBodyClass;
    }
}
