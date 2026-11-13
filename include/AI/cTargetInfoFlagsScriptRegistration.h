// STAND-IN: descriptive registrar name is ours; CD2 slot 1 at 0x8244D8F0 returns eTargetInfoFlags.
// Initializer 0x82F820D8 installs table 0x82000B28 on the four-byte object at 0x8381B240.
#ifndef AI_CTARGETINFOFLAGSSCRIPTREGISTRATION_H
#define AI_CTARGETINFOFLAGSSCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cTargetInfoFlagsScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cTargetInfoFlagsScriptRegistration, CD2_SIZE(cTargetInfoFlagsScriptRegistration, 4))
    };
}
#endif
