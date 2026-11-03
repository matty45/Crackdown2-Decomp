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
