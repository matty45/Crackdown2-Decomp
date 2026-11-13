// STAND-IN: descriptive registrar name is ours. CD2 table 0x820FD9D8 has the common
// enum destructor, eDoorSelection name getter at 0x82411158, and Lua writer at 0x82411200.
#ifndef AI_CDOORSELECTIONSCRIPTREGISTRATION_H
#define AI_CDOORSELECTIONSCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cDoorSelectionScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cDoorSelectionScriptRegistration, CD2_SIZE(cDoorSelectionScriptRegistration, 4))
    };
}
#endif
