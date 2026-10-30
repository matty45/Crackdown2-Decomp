#include "Vehicle/cHelicopterDamageProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cHelicopterDamageProfile::RetClassName() const
    {
        return "cHelicopterDamageProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cHelicopterDamageProfileRegistrar(
        "cHelicopterDamageProfile", cHelicopterDamageProfile::MakeNew, 0x110, false);
}
