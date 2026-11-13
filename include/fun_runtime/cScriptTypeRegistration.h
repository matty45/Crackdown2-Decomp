// STAND-IN: descriptive registrar name is ours. CD2 constructor 0x82772828
// stores child/parent names at +4/+8, initializes two linked lists at +0xC/+0x18,
// and registers the 0x24-byte object with the script system. Its table at
// 0x82147460 contains a deleting destructor and a pure registration method.
#ifndef FUN_RUNTIME_CSCRIPTTYPEREGISTRATION_H
#define FUN_RUNTIME_CSCRIPTTYPEREGISTRATION_H
#include "cd2/layout.h"
#include "fun_runtime/pointer_list.h"
#include "fun_runtime/script_method.h"
namespace Fun_Runtime
{
    class cScriptTypeRegistration
    {
    public:
        cScriptTypeRegistration(const char *name, const char *parentName);
        virtual ~cScriptTypeRegistration(); // CD2 0x827728E0
        virtual void RegisterMethods() = 0;
    private:
        const char *m_pName;
        const char *m_pParentName;
        // List storage is observed in the constructor; element types are unrecovered.
    protected:
        // First list receives the member-method descriptors in RegisterMethods.
        cPointerList<cScriptMethod *> m_lMethods;
        template <class C, class R>
        void RegisterMethod(R (C::*method)() const, const char *name)
        {
            m_lMethods.push_back(CreateConstScriptMethod(name, method));
        }
        template <class C, class R>
        void RegisterMethod(R (C::*method)(), const char *name)
        {
            m_lMethods.push_back(CreateScriptMethod(name, method));
        }
    private:
        // The second list's element protocol remains unrecovered.
        unsigned char m_unmodelledLists[0xC];
        CD2_LAYOUT_CHECKS(cScriptTypeRegistration,
            CD2_SIZE(cScriptTypeRegistration, 0x24)
            CD2_OFFSET(cScriptTypeRegistration, m_pName, 4)
            CD2_OFFSET(cScriptTypeRegistration, m_pParentName, 8)
            CD2_OFFSET(cScriptTypeRegistration, m_lMethods, 0xC)
            CD2_OFFSET(cScriptTypeRegistration, m_unmodelledLists, 0x18))
    };
}
#endif
