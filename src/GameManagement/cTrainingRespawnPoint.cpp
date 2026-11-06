// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cTrainingRespawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cTrainingRespawnPoint::RetClassName() const
    {
        return "cTrainingRespawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cTrainingRespawnPointRegistrar(
        "cTrainingRespawnPoint", cTrainingRespawnPoint::MakeNew, 0x80, false);

    // CD2 0x828586C0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cTrainingRespawnPoint::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingRespawnPoint(packet);
    }
}
