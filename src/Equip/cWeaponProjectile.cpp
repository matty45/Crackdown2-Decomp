#include "Equip/cWeaponProjectile.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cWeaponProjectile::RetClassName() const
    {
        return "cWeaponProjectile";
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cWeaponProjectileRegistrar(
        "cWeaponProjectile", cWeaponProjectile::MakeNew, 0x870, false);
}

#include <new>

// CD2 0x826095F8: placement factory; the constructor stays out of line (a tail call).
namespace Equip
{
    RWS::CAttributeHandler *cWeaponProjectile::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeaponProjectile;
        return 0;
    }
}
