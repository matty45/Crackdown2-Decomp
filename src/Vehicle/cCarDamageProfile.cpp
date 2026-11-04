#include "Vehicle/cCarDamageProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cCarDamageProfile::RetClassName() const
    {
        return "cCarDamageProfile";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cCarDamageProfileRegistrar(
        "cCarDamageProfile", cCarDamageProfile::MakeNew, 0x230, false);
}

#include "cd2/memory.h"

// CD2 0x826A55F0: the class-factory constructor; the constructor stays out of line.
namespace Vehicle
{
    RWS::CAttributeHandler *cCarDamageProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCarDamageProfile;
    }
}
