// STAND-IN: descriptive registrar name is ours. CD2 table 0x8212CF1C names eGameImportance
// through slot 1 (0x82652E90); initializer 0x82FD6DD0 installs it on the four-byte object at
// 0x8383ABB4, immediately after cNonGameBase's script registrar. No own instance fields.
#ifndef GOM_CGAMEIMPORTANCESCRIPTREGISTRATION_H
#define GOM_CGAMEIMPORTANCESCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
class cGameImportanceScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
{
public:
    virtual const char *RetName() const;
    virtual void RegisterValues(lua_State *);
    CD2_LAYOUT_CHECKS(cGameImportanceScriptRegistration, CD2_SIZE(cGameImportanceScriptRegistration, 4))
};
#endif
