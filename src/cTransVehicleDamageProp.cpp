#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cVehicleDamageProp.h"
#include "unknown/cTransVehicleDamageProp.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace unknown
{
    RWS::CAttributeHandler *cTransVehicleDamageProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTransVehicleDamagePropPrototype(packet);
    }

    const char *cTransVehicleDamageProp::RetClassName() const
    {
        return "cTransVehicleDamageProp";
    }

    RWS::CAttributeHandler *cTransVehicleDamageProp::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *memory)
    {
        if (memory)
            return new (memory) cTransVehicleDamageProp(pPrototype);
        return 0;
    }

    // CD2 0x82730E98 has no derived cleanup beyond vtable restoration.
    cTransVehicleDamageProp::~cTransVehicleDamageProp()
    {
    }

    static RWS::CClassFactory::CRegistrar cTransVehicleDamagePropRegistrar(
        "cTransVehicleDamageProp", cTransVehicleDamageProp::MakeNew, 0xEE0, false);

    Fun_Runtime::cClass &cTransVehicleDamageProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTransVehicleDamagePropClass = new Fun_Runtime::cClass(0x14A2D, "cTransVehicleDamageProp", 0xEE0);
        return *cTransVehicleDamagePropClass;
    }

    const Fun_Runtime::cClass *cTransVehicleDamageProp::ms_pcTransVehicleDamagePropClass = &cTransVehicleDamageProp::StaticCreateClass();

    // CD2 0x82FF5A78: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTransVehicleDamagePropcVehicleDamagePropInheritRegistrar(
        unknown::cTransVehicleDamageProp::StaticCreateClass(), Prop::cVehicleDamageProp::StaticCreateClass());

    // CD2 0x82FF5B30: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTransVehicleDamagePropSpawningRegistrar(
        cTransVehicleDamageProp::StaticCreateClass(), cTransVehicleDamageProp::SpawnFromPrototype);
}
