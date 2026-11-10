// Activity/SpawnPoint/cSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SpawnPoint/cSpawnPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Activity/cSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    const Fun_Runtime::cClass &cSpawnPoint::RetClass() const
    {
        return *ms_pcSpawnPointClass;
    }

    Fun_Runtime::cClass &cSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpawnPointClass = new Fun_Runtime::cClass(0x5D1F3, "cSpawnPoint", 0x70);
        return *cSpawnPointClass;
    }

    RWS::CAttributeHandler *cSpawnPoint::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cSpawnPoint *point = new cSpawnPoint;
        point->HandleAttributes(packet);
        return 0;
    }

    const Fun_Runtime::cClass *cSpawnPoint::ms_pcSpawnPointClass = &cSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSpawnPointcSpawnPointBaseInheritRegistrar(
        cSpawnPoint::StaticCreateClass(), cSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cSpawnPointRegistrar(
        "cSpawnPoint", cSpawnPoint::MakeNew, 0x70, false);
}
