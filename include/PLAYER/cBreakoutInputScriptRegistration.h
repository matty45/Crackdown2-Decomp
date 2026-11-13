// STAND-IN: descriptive class name is ours. CD2 table 0x8213D54C has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x8271F150 returning "eBreakoutInput". Four-byte instance: recovered enum registrar base only.
#ifndef PLAYER_CBREAKOUTINPUTSCRIPTREGISTRATION_H
#define PLAYER_CBREAKOUTINPUTSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace PLAYER
{
    class cBreakoutInputScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cBreakoutInputScriptRegistration, CD2_SIZE(cBreakoutInputScriptRegistration, 4))
    };
}

#endif
