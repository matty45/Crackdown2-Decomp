// STAND-IN: descriptive template name is ours. CD2 concrete registrar tables
// replace the base's pure virtual with each type's script-method registration.
#ifndef FUN_RUNTIME_SCRIPT_TYPE_REGISTRAR_H
#define FUN_RUNTIME_SCRIPT_TYPE_REGISTRAR_H
#include "fun_runtime/cScriptTypeRegistration.h"
namespace Fun_Runtime
{
    template <class T> class cScriptTypeRegistrar : public cScriptTypeRegistration
    {
    public:
        cScriptTypeRegistrar(const char *name, const char *parentName)
            : cScriptTypeRegistration(name, parentName) {}
        virtual void RegisterMethods();
    };
}
#endif
