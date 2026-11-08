// Equip/Weapon/cAcidBomblet.cpp: RuffKing's Libraries/Shared/Equipment/Weapon/cAcidBomblet.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cAcidBomblet.h"
#include "cd2/memory.h"

namespace Equip
{
    Fun_Runtime::cClass &cAcidBomblet::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAcidBombletClass = new Fun_Runtime::cClass(0x13267, "cAcidBomblet", 0xB00);
        return *cAcidBombletClass;
    }

    const Fun_Runtime::cClass *cAcidBomblet::ms_pcAcidBombletClass = &cAcidBomblet::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cAcidBombletcCWSatchelChargeInheritRegistrar(
        cAcidBomblet::StaticCreateClass(), cCWSatchelCharge::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAcidBombletRegistrar(
        "cAcidBomblet", cAcidBomblet::MakeNew, 0xB00, false);

    static GOM::cProtoRegistrar cAcidBombletSpawningRegistrar(
        cAcidBomblet::StaticCreateClass(), cAcidBomblet::SpawnFromPrototype);
}
