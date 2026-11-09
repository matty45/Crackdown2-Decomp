// STAND-IN: descriptive class name is ours. CD2 table 0x82113E60 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x8254E8B8 returning "eLODLevel". Instance storage remains unrecovered.
#ifndef CHARACTER_CLODLEVELSCRIPTREGISTRATION_H
#define CHARACTER_CLODLEVELSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace CHARACTER
{
    class cLODLevelScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
    };
}

#endif
