// STAND-IN: descriptive class name is ours. CD2 table 0x82113E60 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x8254E8B8 returning "eLODLevel". Four-byte instance: recovered enum registrar base only.
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
        CD2_LAYOUT_CHECKS(cLODLevelScriptRegistration, CD2_SIZE(cLODLevelScriptRegistration, 4))
    };
}

#endif
