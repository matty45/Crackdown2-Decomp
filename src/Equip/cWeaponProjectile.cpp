#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "Equip/cWeaponProjectile.h"
#include "rws/classfactory.h"

namespace Equip
{
    RWS::CAttributeHandler *cWeaponProjectile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponProjectilePrototype(packet);
    }

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

    const Fun_Runtime::cClass *cWeaponProjectile::ms_pcWeaponProjectileClass = &cWeaponProjectile::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cWeaponProjectilecEquipmentInheritRegistrar(
        cWeaponProjectile::StaticCreateClass(), cEquipment::StaticCreateClass());

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

    Fun_Runtime::cClass &cWeaponProjectile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponProjectileClass = new Fun_Runtime::cClass(0x26EE0, "cWeaponProjectile", 0x870);
        return *cWeaponProjectileClass;
    }
}
