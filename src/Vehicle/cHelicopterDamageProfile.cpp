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

#include "cd2/memory.h"

// CD2 0x826C06D8: the class-factory constructor; the constructor stays out of line.
namespace Vehicle
{
    RWS::CAttributeHandler *cHelicopterDamageProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHelicopterDamageProfile;
    }
}
