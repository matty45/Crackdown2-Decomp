// STAND-IN: descriptive class name is ours. CD2 table 0x820FBF4C has the shared enum destructor,
// name getter 0x823EBF68 returning "eAttackState", and Lua value registration at 0x823EF120.
#ifndef AI_CATTACKSTATESCRIPTREGISTRATION_H
#define AI_CATTACKSTATESCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cAttackStateScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
