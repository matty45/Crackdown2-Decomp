// STAND-IN: descriptive registrar name is ours; CD2 slot 1 at 0x8244D900 returns eTargetEventFlags.
// Initializer 0x82F82120 installs table 0x8210173C on the four-byte object at 0x8381B244.
#ifndef AI_CTARGETEVENTFLAGSSCRIPTREGISTRATION_H
#define AI_CTARGETEVENTFLAGSSCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cTargetEventFlagsScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cTargetEventFlagsScriptRegistration, CD2_SIZE(cTargetEventFlagsScriptRegistration, 4))
    };
}
#endif
