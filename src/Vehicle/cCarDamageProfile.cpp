#include "Vehicle/cCarDamageProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Vehicle
{
    const char *cCarDamageProfile::RetClassName() const
    {
        return "cCarDamageProfile";
    }

    static RWS::CClassFactory::CRegistrar cCarDamageProfileRegistrar(
        "cCarDamageProfile", cCarDamageProfile::MakeNew, 0x230, false);

    // CD2 0x826A55F0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCarDamageProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCarDamageProfile;
    }
}
