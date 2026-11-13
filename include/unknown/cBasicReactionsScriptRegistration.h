// STAND-IN: descriptive registrar name is ours; CD2 getter 0x824549F8 returns eBasicReactions, and RegisterValues 0x82454C70 writes
// its 4 values. Initializer 0x82F85A80 installs table 0x82102250 on the four-byte object at 0x8381C038; at-exit 0x8303AE40
// restores the common table.
#ifndef UNKNOWN_CBASICREACTIONSSCRIPTREGISTRATION_H
#define UNKNOWN_CBASICREACTIONSSCRIPTREGISTRATION_H
#include "fun_runtime/cScriptEnumRegistration.h"
namespace unknown
{
    class cBasicReactionsScriptRegistration : public Fun_Runtime::cScriptEnumRegistration
    {
    public:
        virtual const char *RetName() const;
        virtual void RegisterValues(lua_State *);
        CD2_LAYOUT_CHECKS(cBasicReactionsScriptRegistration, CD2_SIZE(cBasicReactionsScriptRegistration, 4))
    };
}
#endif
