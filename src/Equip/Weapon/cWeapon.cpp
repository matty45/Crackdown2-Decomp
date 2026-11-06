// Script registrar source ownership: CD2 initializer 0x82FCBE80 names cWeapon,
// and cleanup 0x8303F398 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Equip/cWeapon.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

namespace Equip
{
    static Fun_Runtime::cScriptTypeRegistrar<cWeapon> cWeaponScriptRegistrar(
        "cWeapon", "cEquipment");

    Fun_Runtime::cClass &cWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x80, "cWeapon", 0x8C0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cWeapon::ms_pcWeaponClass = &cWeapon::StaticCreateClass();

    const Fun_Runtime::cClass &cWeapon::RetClass() const
    {
        return *ms_pcWeaponClass;
    }
}
