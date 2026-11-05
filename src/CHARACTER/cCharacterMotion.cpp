// Script registrar source ownership: CD2 initializer 0x82FAE158 names cCharacterMotion,
// and cleanup 0x8303CFB0 destroys the same descriptor. Shared interface names are ours.

#include "CHARACTER/cCharacterMotion.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    static Fun_Runtime::cScriptTypeRegistrar<cCharacterMotion> cCharacterMotionScriptRegistrar(
        "cCharacterMotion", "cNetDynamicBody");

    Fun_Runtime::cClass &cCharacterMotion::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x640, "cCharacterMotion", 0x11F0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cCharacterMotion::ms_pcCharacterMotionClass = &cCharacterMotion::StaticCreateClass();

    const Fun_Runtime::cClass &cCharacterMotion::RetClass() const
    {
        return *ms_pcCharacterMotionClass;
    }
}
