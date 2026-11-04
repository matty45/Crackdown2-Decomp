#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "Vehicle/cHelicopter.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cHelicopter::RetClassName() const
    {
        return "cHelicopter";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cHelicopterRegistrar(
        "cHelicopter", cHelicopter::MakeNew, 0x2DB0, false);
}

#include "cd2/memory.h"

namespace Vehicle
{
    Fun_Runtime::cClass &cHelicopter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHelicopterClass = new Fun_Runtime::cClass(0x675, "cHelicopter", 0x2DB0);
        return *cHelicopterClass;
    }
}

namespace Vehicle
{
    const Fun_Runtime::cClass *cHelicopter::ms_pcHelicopterClass = &cHelicopter::StaticCreateClass();
}

// CD2 0x82FE84E8: runtime class inheritance registration.
namespace Vehicle
{
    static Fun_Runtime::cInheritanceRegistrar cHelicoptercVehicleInheritRegistrar(
        Vehicle::cHelicopter::StaticCreateClass(), Vehicle::cVehicle::StaticCreateClass());
}

#include <new>

// CD2 0x826B8AE0: placement factory; the constructor stays out of line (a tail call).
namespace Vehicle
{
    RWS::CAttributeHandler *cHelicopter::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cHelicopter;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FE85A0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace Vehicle
{
    static GOM::cProtoRegistrar cHelicopterSpawningRegistrar(
        cHelicopter::StaticCreateClass(), cHelicopter::SpawnFromPrototype);
}

// CD2 0x826B8A78: the class-factory constructor; the constructor stays out of line.
namespace Vehicle
{
    RWS::CAttributeHandler *cHelicopter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHelicopter(packet);
    }
}
