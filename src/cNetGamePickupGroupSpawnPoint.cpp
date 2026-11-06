// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "unknown/cNetGamePickupGroupSpawnPoint.h"

namespace unknown
{
    const char *cNetGamePickupGroupSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupGroupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGamePickupGroupSpawnPointRegistrar(
        "cNetGamePickupGroupSpawnPoint", cNetGamePickupGroupSpawnPoint::MakeNew, 0x120, false);
}
