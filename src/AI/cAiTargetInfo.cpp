// Script registrar source ownership: CD2 initializer 0x82F82080 names cAiTargetInfo,
// and cleanup 0x8303AB88 destroys the same descriptor. Shared interface names are ours.
#include "AI/cAiTargetInfo.h"
#include "fun_runtime/script_type_registrar.h"

namespace AI
{
    static Fun_Runtime::cScriptTypeRegistrar<cAiTargetInfo> cAiTargetInfoScriptRegistrar(
        "cAiTargetInfo", "cScriptHost");
}
