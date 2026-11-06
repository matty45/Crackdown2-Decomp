// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cCHordeCaptureZone.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCHordeCaptureZone::RetClassName() const
    {
        return "cCHordeCaptureZone";
    }

    static RWS::CClassFactory::CRegistrar cCHordeCaptureZoneRegistrar(
        "cCHordeCaptureZone", cCHordeCaptureZone::MakeNew, 0x390, false);

    // CD2 0x82858CD0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCHordeCaptureZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeCaptureZone(packet);
    }
}
