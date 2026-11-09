// STAND-IN: descriptive class name is ours. CD2 table 0x820FBF28 has the shared enum destructor,
// name getter 0x823EBF38 returning "eMovementType", and Lua value registration at 0x823EECB0.
#ifndef AI_CMOVEMENTTYPESCRIPTREGISTRATION_H
#define AI_CMOVEMENTTYPESCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cMovementTypeScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
