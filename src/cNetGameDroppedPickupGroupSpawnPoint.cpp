// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "unknown/cNetGameDroppedPickupGroupSpawnPoint.h"

namespace unknown
{
    const char *cNetGameDroppedPickupGroupSpawnPoint::RetClassName() const
    {
        return "cNetGameDroppedPickupGroupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGameDroppedPickupGroupSpawnPointRegistrar(
        "cNetGameDroppedPickupGroupSpawnPoint", cNetGameDroppedPickupGroupSpawnPoint::MakeNew, 0x3d0, false);
}
