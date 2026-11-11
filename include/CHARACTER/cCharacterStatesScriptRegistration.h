// STAND-IN: descriptive class name is ours. CD2 enum table 0x82112CA8 has
// slot-1 getter 0x825402E8 ("eCharacterStates") and Lua registration at
// 0x82540308. These are separate from cCwCharacterStateProfile's object table.
#ifndef CHARACTER_CCHARACTERSTATESSCRIPTREGISTRATION_H
#define CHARACTER_CCHARACTERSTATESSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace CHARACTER
{
    class cCharacterStatesScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
