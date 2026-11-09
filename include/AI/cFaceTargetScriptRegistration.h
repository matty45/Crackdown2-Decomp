// STAND-IN: descriptive class name is ours. CD2 table 0x820FBF40 has the shared enum destructor,
// name getter 0x823EBF58 returning "eFaceTarget", and Lua value registration at 0x823EEF80.
#ifndef AI_CFACETARGETSCRIPTREGISTRATION_H
#define AI_CFACETARGETSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cFaceTargetScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
