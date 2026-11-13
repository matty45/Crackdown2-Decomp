// STAND-IN: descriptive class name is ours. CD2 table 0x821138FC has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x82543048 returning "eBones". Four-byte instance: recovered enum registrar base only.
#ifndef CHARACTER_CBONESSCRIPTREGISTRATION_H
#define CHARACTER_CBONESSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace CHARACTER
{
    class cBonesScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cBonesScriptRegistration, CD2_SIZE(cBonesScriptRegistration, 4))
    };
}

#endif
