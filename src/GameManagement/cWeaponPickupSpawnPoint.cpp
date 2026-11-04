#include "rws/classfactory.h"
#include "GameManagement/cWeaponPickupSpawnPoint.h"

namespace GameManagement
{
    const char *cWeaponPickupSpawnPoint::RetClassName() const
    {
        return "cWeaponPickupSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cWeaponPickupSpawnPointRegistrar(
        "cWeaponPickupSpawnPoint", cWeaponPickupSpawnPoint::MakeNew, 0xd0, false);
}

#include "cd2/memory.h"

// CD2 0x8284C5C8: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cWeaponPickupSpawnPoint::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponPickupSpawnPoint(packet);
    }
}
