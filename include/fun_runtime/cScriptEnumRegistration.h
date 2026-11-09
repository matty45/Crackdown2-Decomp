// STAND-IN: descriptive class and method names are ours. CD2 enum tables have three slots:
// deleting destructor, enum-name getter, and Lua value registration. The tables at 0x820FBF28..0x820FBF64
// share destructor 0x823EC238, which restores the common table at 0x82147468. Slot 2 at 0x823EECB0
// takes lua_State* in r4 and fills the enum table. Instance storage is not recovered here.
#ifndef FUN_RUNTIME_CSCRIPTENUMREGISTRATION_H
#define FUN_RUNTIME_CSCRIPTENUMREGISTRATION_H

struct lua_State;

namespace Fun_Runtime
{
    class cScriptEnumRegistration
    {
    public:
        virtual ~cScriptEnumRegistration();
        virtual const char *RetName() const = 0;
        virtual void RegisterValues(lua_State *) = 0;
    };
}

#endif
