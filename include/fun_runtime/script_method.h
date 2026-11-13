// STAND-IN: descriptive method-descriptor name is ours. CD2 factories allocate
// 16 bytes: a one-slot invocation vptr, borrowed name at +4, and an eight-byte
// member-function pointer at +8. The common factory ABI passes that pointer in r4.
#ifndef FUN_RUNTIME_SCRIPT_METHOD_H
#define FUN_RUNTIME_SCRIPT_METHOD_H
#include "cd2/layout.h"
struct lua_State;
namespace Fun_Runtime
{
    class cScriptMethod
    {
    public:
        virtual int Invoke(lua_State *) = 0;
    protected:
        explicit cScriptMethod(const char *name) : m_pName(name) {}
        const char *m_pName;
        CD2_LAYOUT_CHECKS(cScriptMethod,
            CD2_SIZE(cScriptMethod, 8)
            CD2_OFFSET(cScriptMethod, m_pName, 4))
    };

    template <class C, class R>
    cScriptMethod *CreateConstScriptMethod(const char *, R (C::*)() const);
    template <class C, class R>
    cScriptMethod *CreateScriptMethod(const char *, R (C::*)());
}

#endif
