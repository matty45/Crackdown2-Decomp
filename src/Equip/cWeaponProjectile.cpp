#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "Equip/cWeaponProjectile.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cWeaponProjectile::RetClassName() const
    {
        return "cWeaponProjectile";
    }

    // CD2 0x82609610 and 0x826096C0: no derived construction or cleanup beyond the vtables.
    cWeaponProjectile::cWeaponProjectile()
    {
    }

    cWeaponProjectile::~cWeaponProjectile()
    {
    }

    static RWS::CClassFactory::CRegistrar cWeaponProjectileRegistrar(
        "cWeaponProjectile", cWeaponProjectile::MakeNew, 0x870, false);

    // CD2 0x82FCBFB8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cWeaponProjectileSpawningRegistrar(
        cWeaponProjectile::StaticCreateClass(), cWeaponProjectile::SpawnFromPrototype);

    RWS::CAttributeHandler *cWeaponProjectile::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeaponProjectile;
        return 0;
    }
}
