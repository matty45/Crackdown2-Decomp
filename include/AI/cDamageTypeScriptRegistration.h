// STAND-IN: descriptive registrar name is ours; CD2 getter 0x82441200 returns eDamageType.
// Initializer 0x82F7ACD0 installs table 0x82100468 on the four-byte object at 0x83818CCC.
#ifndef AI_CDAMAGETYPESCRIPTREGISTRATION_H
#define AI_CDAMAGETYPESCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace AI
{
    class cDamageTypeScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cDamageTypeScriptRegistration, CD2_SIZE(cDamageTypeScriptRegistration, 4))
    };
}
#endif
