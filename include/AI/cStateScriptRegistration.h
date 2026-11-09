// STAND-IN: descriptive class name is ours. CD2 table 0x820FBF58 has the shared enum destructor,
// name getter 0x823EBF78 returning "eState", and Lua value registration at 0x823EF068.
#ifndef AI_CSTATESCRIPTREGISTRATION_H
#define AI_CSTATESCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cStateScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
