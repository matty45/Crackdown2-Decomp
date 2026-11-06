// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "GameManagement/cNetGamePickupSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cNetGamePickupSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cNetGamePickupSpawnPoint;
    }

    const char *cNetGamePickupSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGamePickupSpawnPointRegistrar(
        "cNetGamePickupSpawnPoint", cNetGamePickupSpawnPoint::MakeNew, 0xa0, false);
}
