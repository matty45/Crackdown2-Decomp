// VFX/cLinkedVFXSpawner.cpp: RuffKing's Libraries/Shared/VFX/cLinkedVFXSpawner.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "VFX/cLinkedVFXSpawner.h"
#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cLinkedVFXSpawner::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLinkedVFXSpawnerClass = new Fun_Runtime::cClass(0x5086D, "cLinkedVFXSpawner", 0x70);
        return *cLinkedVFXSpawnerClass;
    }

    const Fun_Runtime::cClass *cLinkedVFXSpawner::ms_pcLinkedVFXSpawnerClass = &cLinkedVFXSpawner::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cLinkedVFXSpawnerRegistrar(
        "cLinkedVFXSpawner", cLinkedVFXSpawner::MakeNew, 0x70, false);

    static Fun_Runtime::cInheritanceRegistrar cLinkedVFXSpawnercAmbientVFXSpawnerBaseInheritRegistrar(
        cLinkedVFXSpawner::StaticCreateClass(), cAmbientVFXSpawnerBase::StaticCreateClass());
}
