// VFX/cPlaceableLight.cpp: RuffKing's Libraries/Shared/VFX/cPlaceableLight.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "VFX/cPlaceableLight.h"
#include "cd2/memory.h"

namespace VFX
{
    const Fun_Runtime::cClass &cPlaceableLight::RetClass() const
    {
        return *ms_pcPlaceableLightClass;
    }

    Fun_Runtime::cClass &cPlaceableLight::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPlaceableLightClass = new Fun_Runtime::cClass(0x5D1F6, "cPlaceableLight", 0x80);
        return *cPlaceableLightClass;
    }

    const Fun_Runtime::cClass *cPlaceableLight::ms_pcPlaceableLightClass = &cPlaceableLight::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cPlaceableLightcSpawnPointInheritRegistrar(
        cPlaceableLight::StaticCreateClass(), Activity::cSpawnPoint::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cPlaceableLightRegistrar(
        "cPlaceableLight", cPlaceableLight::MakeNew, 0x80, false);
}
