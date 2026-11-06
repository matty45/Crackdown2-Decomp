// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "rws/classfactory.h"
#include "GameManagement/cWeaponPickupSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cWeaponPickupSpawnPoint::RetClassName() const
    {
        return "cWeaponPickupSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cWeaponPickupSpawnPointRegistrar(
        "cWeaponPickupSpawnPoint", cWeaponPickupSpawnPoint::MakeNew, 0xd0, false);

    // CD2 0x8284C5C8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cWeaponPickupSpawnPoint::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponPickupSpawnPoint(packet);
    }
}
