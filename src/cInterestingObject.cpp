// Script registrar source ownership: CD2 initializer 0x82F85AC8 names cInterestingObject,
// and cleanup 0x8303AE58 destroys the same descriptor. Shared interface names are ours.
#include "unknown/cInterestingObject.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    static Fun_Runtime::cScriptTypeRegistrar<cInterestingObject> cInterestingObjectScriptRegistrar(
        "cInterestingObject", "cScriptHost");
}

#include "cd2/memory.h"

namespace unknown
{
    Fun_Runtime::cClass &cInterestingObject::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3EA, "cInterestingObject", 0x40);
        return *descriptor;
    }
}

namespace unknown
{
    const Fun_Runtime::cClass *cInterestingObject::ms_pcInterestingObjectClass = &cInterestingObject::StaticCreateClass();
}
