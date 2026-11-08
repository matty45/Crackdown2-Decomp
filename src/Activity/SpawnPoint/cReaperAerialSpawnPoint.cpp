// Activity/SpawnPoint/cReaperAerialSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SpawnPoint/cReaperAerialSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Activity/cReaperAerialSpawnPoint.h"
#include "Activity/cReaperAerialRespawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cReaperAerialSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cReaperAerialSpawnPointClass = new Fun_Runtime::cClass(0x5D1FA, "cReaperAerialSpawnPoint", 0xB0);
        return *cReaperAerialSpawnPointClass;
    }

    const Fun_Runtime::cClass *cReaperAerialSpawnPoint::ms_pcReaperAerialSpawnPointClass = &cReaperAerialSpawnPoint::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cReaperAerialSpawnPointRegistrar(
        "cReaperAerialSpawnPoint", cReaperAerialSpawnPoint::MakeNew, 0xB0, false);

    static Fun_Runtime::cInheritanceRegistrar cReaperAerialSpawnPointcSquadMemberSpawnPointInheritRegistrar(
        cReaperAerialSpawnPoint::StaticCreateClass(), cSquadMemberSpawnPoint::StaticCreateClass());

    Fun_Runtime::cClass &cReaperAerialRespawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cReaperAerialRespawnPointClass = new Fun_Runtime::cClass(0x5D1FB, "cReaperAerialRespawnPoint", 0x90);
        return *cReaperAerialRespawnPointClass;
    }

    const Fun_Runtime::cClass *cReaperAerialRespawnPoint::ms_pcReaperAerialRespawnPointClass = &cReaperAerialRespawnPoint::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cReaperAerialRespawnPointRegistrar(
        "cReaperAerialRespawnPoint", cReaperAerialRespawnPoint::MakeNew, 0x90, false);

    static Fun_Runtime::cInheritanceRegistrar cReaperAerialRespawnPointcSquadMemberRespawnPointInheritRegistrar(
        cReaperAerialRespawnPoint::StaticCreateClass(), cSquadMemberRespawnPoint::StaticCreateClass());
}
