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
