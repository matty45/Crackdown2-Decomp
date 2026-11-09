// STAND-IN: descriptive class name is ours. CD2 table 0x820FBF34 has the shared enum destructor,
// name getter 0x823EBF48 returning "ePerceptionOptions", and Lua value registration at 0x823EEDA0.
#ifndef AI_CPERCEPTIONOPTIONSSCRIPTREGISTRATION_H
#define AI_CPERCEPTIONOPTIONSSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cPerceptionOptionsScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
