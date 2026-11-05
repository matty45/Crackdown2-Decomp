#include "Vehicle/cHelicopterDamageProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Vehicle
{
    const char *cHelicopterDamageProfile::RetClassName() const
    {
        return "cHelicopterDamageProfile";
    }

    static RWS::CClassFactory::CRegistrar cHelicopterDamageProfileRegistrar(
        "cHelicopterDamageProfile", cHelicopterDamageProfile::MakeNew, 0x110, false);

    // CD2 0x826C06D8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cHelicopterDamageProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cHelicopterDamageProfile;
    }
}
