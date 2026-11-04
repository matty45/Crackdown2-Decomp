#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cVehicleDamageProp.h"
#include "unknown/cTransVehicleDamageProp.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cTransVehicleDamageProp::RetClassName() const
    {
        return "cTransVehicleDamageProp";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cTransVehicleDamagePropRegistrar(
        "cTransVehicleDamageProp", cTransVehicleDamageProp::MakeNew, 0xEE0, false);
}

#include "cd2/memory.h"

namespace unknown
{
    Fun_Runtime::cClass &cTransVehicleDamageProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTransVehicleDamagePropClass = new Fun_Runtime::cClass(0x14A2D, "cTransVehicleDamageProp", 0xEE0);
        return *cTransVehicleDamagePropClass;
    }
}

namespace unknown
{
    const Fun_Runtime::cClass *cTransVehicleDamageProp::ms_pcTransVehicleDamagePropClass = &cTransVehicleDamageProp::StaticCreateClass();
}

// CD2 0x82FF5A78: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cTransVehicleDamagePropcVehicleDamagePropInheritRegistrar(
        unknown::cTransVehicleDamageProp::StaticCreateClass(), Prop::cVehicleDamageProp::StaticCreateClass());
}

#include <new>

// CD2 0x82730CB8: placement factory; the constructor stays out of line (a tail call).
namespace unknown
{
    RWS::CAttributeHandler *cTransVehicleDamageProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cTransVehicleDamageProp(prototype);
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FF5B30: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cTransVehicleDamagePropSpawningRegistrar(
        cTransVehicleDamageProp::StaticCreateClass(), cTransVehicleDamageProp::SpawnFromPrototype);
}

// CD2 0x82730c38: the class factory builds the prototype.
namespace unknown
{
    RWS::CAttributeHandler *cTransVehicleDamageProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTransVehicleDamagePropPrototype(packet);
    }
}
