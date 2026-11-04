#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "Vehicle/cLandVehicle.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cLandVehicle::RetClassName() const
    {
        return "cLandVehicle";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cLandVehicleRegistrar(
        "cLandVehicle", cLandVehicle::MakeNew, 0x28C0, false);
}

#include "cd2/memory.h"

namespace Vehicle
{
    Fun_Runtime::cClass &cLandVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLandVehicleClass = new Fun_Runtime::cClass(0x642, "cLandVehicle", 0x28C0);
        return *cLandVehicleClass;
    }
}

namespace Vehicle
{
    const Fun_Runtime::cClass *cLandVehicle::ms_pcLandVehicleClass = &cLandVehicle::StaticCreateClass();
}

// CD2 0x82FE89B8: runtime class inheritance registration.
namespace Vehicle
{
    static Fun_Runtime::cInheritanceRegistrar cLandVehiclecVehicleInheritRegistrar(
        Vehicle::cLandVehicle::StaticCreateClass(), Vehicle::cVehicle::StaticCreateClass());
}

#include <new>

// CD2 0x826C0E20: placement factory; the constructor stays out of line (a tail call).
namespace Vehicle
{
    RWS::CAttributeHandler *cLandVehicle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cLandVehicle;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FE8A70: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace Vehicle
{
    static GOM::cProtoRegistrar cLandVehicleSpawningRegistrar(
        cLandVehicle::StaticCreateClass(), cLandVehicle::SpawnFromPrototype);
}
