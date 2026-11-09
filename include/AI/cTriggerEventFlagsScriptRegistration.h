// STAND-IN: descriptive class name is ours. CD2 table 0x820FB0F0 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x823E7988 returning "eTriggerEventFlags". Instance storage remains unrecovered.
#ifndef AI_CTRIGGEREVENTFLAGSSCRIPTREGISTRATION_H
#define AI_CTRIGGEREVENTFLAGSSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cTriggerEventFlagsScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
