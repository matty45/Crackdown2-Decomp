// PHYSICS/cNetDynamicBody.cpp: RuffKing's Libraries/Shared/Physics/cNetDynamicBody.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    Fun_Runtime::cClass &cNetDynamicBody::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cNetDynamicBodyClass = new Fun_Runtime::cClass(0x648, "cNetDynamicBody", 0x7A0);
        return *cNetDynamicBodyClass;
    }

    const Fun_Runtime::cClass *cNetDynamicBody::ms_pcNetDynamicBodyClass = &cNetDynamicBody::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cNetDynamicBodycDynamicBodyInheritRegistrar(
        cNetDynamicBody::StaticCreateClass(), cDynamicBody::StaticCreateClass());
}
