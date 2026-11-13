// STAND-IN: descriptive class and method names are ours. CD2 enum tables have three slots:
// deleting destructor, enum-name getter, and Lua value registration. The tables at 0x820FBF28..0x820FBF64
// share destructor 0x823EC238, which restores the common table at 0x82147468. Slot 2 at 0x823EECB0
// takes lua_State* in r4 and fills the enum table. CD2 constructor 0x827729A8 writes only the vptr.
// Character-state registrar at 0x83823F10 ends before Ret_OK at 0x83823F14: four bytes total.
#ifndef FUN_RUNTIME_CSCRIPTENUMREGISTRATION_H
#define FUN_RUNTIME_CSCRIPTENUMREGISTRATION_H

#include "cd2/layout.h"

struct lua_State;

namespace Fun_Runtime
{
    class cScriptEnumRegistration
    {
    public:
        cScriptEnumRegistration(); // CD2 0x827729A8 also registers this object with the script system.
        // CD2 at-exit 0x8303CE60 restores the common table; there is no member cleanup.
        virtual ~cScriptEnumRegistration() {}
        virtual const char *RetName() const = 0;
        virtual void RegisterValues(lua_State *) = 0;
        CD2_LAYOUT_CHECKS(cScriptEnumRegistration, CD2_SIZE(cScriptEnumRegistration, 4))
    };
}

#endif
