// CHARACTER/cWingSuitUpdraftZone.cpp: RuffKing's Libraries/Shared/Character/cWingSuitUpdraftZone.cpp.
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
#include "CHARACTER/cWingSuitUpdraftZoneProfile.h"
#include "CHARACTER/cWingSuitUpdraftZone.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    RWS::CAttributeHandler *cWingSuitUpdraftZoneProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWingSuitUpdraftZoneProfile(packet);
    }

    const char *cWingSuitUpdraftZoneProfile::RetClassName() const
    {
        return "cWingSuitUpdraftZoneProfile";
    }

    RWS::CAttributeHandler *cWingSuitUpdraftZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWingSuitUpdraftZone(packet);
    }

    const char *cWingSuitUpdraftZone::RetClassName() const
    {
        return "cWingSuitUpdraftZone";
    }

    static RWS::CClassFactory::CRegistrar cWingSuitUpdraftZoneProfileRegistrar(
        "cWingSuitUpdraftZoneProfile", cWingSuitUpdraftZoneProfile::MakeNew, 0x3C, false);

    static RWS::CClassFactory::CRegistrar cWingSuitUpdraftZoneRegistrar(
        "cWingSuitUpdraftZone", cWingSuitUpdraftZone::MakeNew, 0x110, false);
}
