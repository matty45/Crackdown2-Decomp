// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cCHordeProfile.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCHordeProfile::RetClassName() const
    {
        return "cCHordeProfile";
    }

    static RWS::CClassFactory::CRegistrar cCHordeProfileRegistrar(
        "cCHordeProfile", cCHordeProfile::MakeNew, 0xd8, false);

    // CD2 0x82865320: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCHordeProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCHordeProfile;
    }
}
