// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cHordeBeam.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cHordeBeam::RetClassName() const
    {
        return "cHordeBeam";
    }

    static RWS::CClassFactory::CRegistrar cHordeBeamRegistrar(
        "cHordeBeam", cHordeBeam::MakeNew, 0xa0, false);

    // CD2 0x82867908: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cHordeBeam::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHordeBeam(packet);
    }
}
