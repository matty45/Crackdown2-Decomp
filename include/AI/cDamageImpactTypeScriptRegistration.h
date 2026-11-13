// STAND-IN: descriptive registrar name is ours; CD2 getter 0x82441210 returns eDamageImpactType.
// Initializer 0x82F7AD18 installs table 0x82100474 on the four-byte object at 0x83818CD0.
#ifndef AI_CDAMAGEIMPACTTYPESCRIPTREGISTRATION_H
#define AI_CDAMAGEIMPACTTYPESCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cDamageImpactTypeScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cDamageImpactTypeScriptRegistration, CD2_SIZE(cDamageImpactTypeScriptRegistration, 4))
    };
}
#endif
