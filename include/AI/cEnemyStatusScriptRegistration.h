// STAND-IN: descriptive class name is ours. CD2 table 0x820FB0FC has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x823E7998 returning "eEnemyStatus". Four-byte instance: recovered enum registrar base only.
#ifndef AI_CENEMYSTATUSSCRIPTREGISTRATION_H
#define AI_CENEMYSTATUSSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cEnemyStatusScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cEnemyStatusScriptRegistration, CD2_SIZE(cEnemyStatusScriptRegistration, 4))
    };
}

#endif
