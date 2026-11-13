// STAND-IN: descriptive class name is ours. CD2 table 0x82155B00 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x8280C078 returning "ePopTOD". Four-byte instance: recovered enum registrar base only.
#ifndef UNKNOWN_CPOPTODSCRIPTREGISTRATION_H
#define UNKNOWN_CPOPTODSCRIPTREGISTRATION_H

#include "fun_runtime/cScriptEnumRegistration.h"

namespace unknown
{
    class cPopTODScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cPopTODScriptRegistration, CD2_SIZE(cPopTODScriptRegistration, 4))
    };
}

#endif
