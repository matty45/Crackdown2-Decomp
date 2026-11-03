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
