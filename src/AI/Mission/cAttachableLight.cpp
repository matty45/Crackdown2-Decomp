// AI/Mission/cAttachableLight.cpp: RuffKing's Libraries/Shared/AI/Mission/cAttachableLight.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cAttachableLight.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAttachableLight::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAttachableLightClass = new Fun_Runtime::cClass(0x5D1F8, "cAttachableLight", 0x160);
        return *cAttachableLightClass;
    }

    const Fun_Runtime::cClass *cAttachableLight::ms_pcAttachableLightClass = &cAttachableLight::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cAttachableLightcPlaceableLightInheritRegistrar(
        cAttachableLight::StaticCreateClass(), VFX::cPlaceableLight::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAttachableLightRegistrar(
        "cAttachableLight", cAttachableLight::MakeNew, 0x160, false);
}
