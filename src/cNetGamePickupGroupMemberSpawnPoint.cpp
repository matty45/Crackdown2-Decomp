// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "unknown/cNetGamePickupGroupMemberSpawnPoint.h"

namespace unknown
{
    const char *cNetGamePickupGroupMemberSpawnPoint::RetClassName() const
    {
        return "cNetGamePickupGroupMemberSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cNetGamePickupGroupMemberSpawnPointRegistrar(
        "cNetGamePickupGroupMemberSpawnPoint", cNetGamePickupGroupMemberSpawnPoint::MakeNew, 0xa0, false);
}
