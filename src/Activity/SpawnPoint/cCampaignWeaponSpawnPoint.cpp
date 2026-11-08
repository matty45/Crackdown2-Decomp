// Activity/SpawnPoint/cCampaignWeaponSpawnPoint.cpp: RuffKing's Libraries/Shared/ActivityManager/SpawnPoint/cCampaignWeaponSpawnPoint.cpp.
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
#include "Activity/cCampaignWeaponSpawnPoint.h"
#include "cd2/memory.h"

namespace Activity
{
    Fun_Runtime::cClass &cCampaignWeaponSpawnPoint::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCampaignWeaponSpawnPointClass = new Fun_Runtime::cClass(0x5D220, "cCampaignWeaponSpawnPoint", 0xA0);
        return *cCampaignWeaponSpawnPointClass;
    }

    const Fun_Runtime::cClass *cCampaignWeaponSpawnPoint::ms_pcCampaignWeaponSpawnPointClass = &cCampaignWeaponSpawnPoint::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cCampaignWeaponSpawnPointcSpawnPointBaseInheritRegistrar(
        cCampaignWeaponSpawnPoint::StaticCreateClass(), cSpawnPointBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cCampaignWeaponSpawnPointRegistrar(
        "cCampaignWeaponSpawnPoint", cCampaignWeaponSpawnPoint::MakeNew, 0xA0, false);
}
