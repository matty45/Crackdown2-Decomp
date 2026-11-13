// STAND-IN: descriptive const-member descriptor name is ours. CD2 factories
// 0x8260A840/0x8260A8A0/0x8273D230 store the name and eight-byte member pointer
// in a 16-byte allocation. Each result type has a one-slot invocation table.
#ifndef FUN_RUNTIME_CONST_SCRIPT_METHOD_H
#define FUN_RUNTIME_CONST_SCRIPT_METHOD_H
#include "fun_runtime/script_method.h"
namespace Fun_Runtime
{
    template <class C, class R>
    class cConstScriptMethod : public cScriptMethod
    {
    public:
        cConstScriptMethod(const char *name, R (C::*method)() const)
            : cScriptMethod(name), m_pMethod(method)
        {
        }
        virtual int Invoke(lua_State *);
    private:
        R (C::*m_pMethod)() const;
        CD2_LAYOUT_CHECKS(cConstScriptMethod,
            CD2_SIZE(cConstScriptMethod, 0x10)
            CD2_OFFSET(cConstScriptMethod, m_pMethod, 8))
    };

    template <class C, class R>
    cScriptMethod *CreateConstScriptMethod(const char *name, R (C::*method)() const)
    {
        return new cConstScriptMethod<C, R>(name, method);
    }
}
#endif
