// PHYSICS/cUniqueStuntZone.cpp: RuffKing's Libraries/Shared/Physics/cUniqueStuntZone.cpp.
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
#include "rws/classfactory.h"
#include "PHYSICS/cStuntRing.h"
#include "PHYSICS/cStunt.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    Fun_Runtime::cClass &cStuntRing::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStuntRingClass = new Fun_Runtime::cClass(0x110, "cStuntRing", 0x1C0);
        return *cStuntRingClass;
    }

    static RWS::CClassFactory::CRegistrar cStuntRingRegistrar(
        "cStuntRing", cStuntRing::MakeNew, 0x1C0, false);

    const Fun_Runtime::cClass *cStuntRing::ms_pcStuntRingClass = &cStuntRing::StaticCreateClass();

    Fun_Runtime::cClass &cStunt::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStuntClass = new Fun_Runtime::cClass(0x111, "cStunt", 0xEC);
        return *cStuntClass;
    }

    static RWS::CClassFactory::CRegistrar cStuntRegistrar(
        "cStunt", cStunt::MakeNew, 0xEC, false);

    const Fun_Runtime::cClass *cStunt::ms_pcStuntClass = &cStunt::StaticCreateClass();
}
