// STAND-IN: descriptive mutable-member descriptor name is ours. CD2's bool
// factory 0x8273D230 is shared by const and mutable no-argument member methods.
// Both carry the borrowed name at +4 and a native eight-byte member pointer +8.
#ifndef FUN_RUNTIME_MEMBER_SCRIPT_METHOD_H
#define FUN_RUNTIME_MEMBER_SCRIPT_METHOD_H
#include "fun_runtime/script_method.h"
namespace Fun_Runtime
{
    template <class C, class R>
    class cMemberScriptMethod : public cScriptMethod
    {
    public:
        cMemberScriptMethod(const char *name, R (C::*method)())
            : cScriptMethod(name), m_pMethod(method) {}
        virtual int Invoke(lua_State *);
    private:
        R (C::*m_pMethod)();
        CD2_LAYOUT_CHECKS(cMemberScriptMethod,
            CD2_SIZE(cMemberScriptMethod, 0x10)
            CD2_OFFSET(cMemberScriptMethod, m_pMethod, 8))
    };

    template <class C, class R>
    cScriptMethod *CreateScriptMethod(const char *name, R (C::*method)())
    {
        return new cMemberScriptMethod<C, R>(name, method);
    }
}
#endif
