// Script registrar source ownership: CD2 initializer 0x82F85AC8 names cInterestingObject,
// and cleanup 0x8303AE58 destroys the same descriptor. Shared interface names are ours.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cInterestingObject.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/memory.h"

namespace unknown
{
    static Fun_Runtime::cScriptTypeRegistrar<cInterestingObject> cInterestingObjectScriptRegistrar(
        "cInterestingObject", "cScriptHost");

    Fun_Runtime::cClass &cInterestingObject::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3EA, "cInterestingObject", 0x40);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cInterestingObject::ms_pcInterestingObjectClass = &cInterestingObject::StaticCreateClass();
}
