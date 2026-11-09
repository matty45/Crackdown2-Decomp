// STAND-IN: descriptive class name is ours. CD2 table 0x820FB108 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x823E79A8 returning "eMapStatus". Instance storage remains unrecovered.
#ifndef AI_CMAPSTATUSSCRIPTREGISTRATION_H
#define AI_CMAPSTATUSSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace AI
{
    class cMapStatusScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
