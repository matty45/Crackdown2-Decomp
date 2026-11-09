// STAND-IN: descriptive class name is ours. CD2 table 0x82155B00 has the shared enum destructor
// 0x823EC238 and slot-1 getter 0x8280C078 returning "ePopTOD". Instance storage remains unrecovered.
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
    };
}

#endif
