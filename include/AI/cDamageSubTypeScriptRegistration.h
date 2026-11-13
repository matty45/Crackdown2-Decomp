// STAND-IN: descriptive registrar name is ours; CD2 getter 0x82441220 returns eDamageSubType.
// Initializer 0x82F7AD60 installs table 0x82100480 on the four-byte object at 0x83818CD4.
#ifndef AI_CDAMAGESUBTYPESCRIPTREGISTRATION_H
#define AI_CDAMAGESUBTYPESCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cDamageSubTypeScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cDamageSubTypeScriptRegistration, CD2_SIZE(cDamageSubTypeScriptRegistration, 4))
    };
}
#endif
