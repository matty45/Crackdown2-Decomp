// Script registrar source ownership: CD2 initializer 0x83000A00 names cScriptHost,
// and cleanup 0x83041F30 destroys the same descriptor. Shared interface names are ours.
#include "fun_runtime/scripthost.h"
#include "fun_runtime/script_type_registrar.h"

namespace Fun_Runtime
{
    static Fun_Runtime::cScriptTypeRegistrar<cScriptHost> cScriptHostScriptRegistrar(
        "cScriptHost", "Host");
}

#include "cd2/memory.h"

namespace Fun_Runtime
{
    Fun_Runtime::cClass &cScriptHost::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3F1, "cScriptHost", 0x1C);
        return *descriptor;
    }
}

namespace Fun_Runtime
{
    const Fun_Runtime::cClass *cScriptHost::ms_pcScriptHostClass = &cScriptHost::StaticCreateClass();

}
