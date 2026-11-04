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
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cWeaponProjectileRegistrar(
        "cWeaponProjectile", cWeaponProjectile::MakeNew, 0x870, false);
}

// CD2 0x82FCBFB8: register the class descriptor and placement factory.
namespace Equip
{
    static GOM::cProtoRegistrar cWeaponProjectileSpawningRegistrar(
        cWeaponProjectile::StaticCreateClass(), cWeaponProjectile::SpawnFromPrototype);
}

namespace Equip
{
    RWS::CAttributeHandler *cWeaponProjectile::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeaponProjectile;
        return 0;
    }
}
