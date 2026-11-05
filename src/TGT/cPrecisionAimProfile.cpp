#include "rws/classfactory.h"
#include "TGT/cPrecisionAimProfile.h"
#include "cd2/memory.h"

namespace TGT
{
    const char *cPrecisionAimProfile::RetClassName() const
    {
        return "cPrecisionAimProfile";
    }

    static RWS::CClassFactory::CRegistrar cPrecisionAimProfileRegistrar(
        "cPrecisionAimProfile", cPrecisionAimProfile::MakeNew, 0x18, false);

    // CD2 0x8277D200: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cPrecisionAimProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPrecisionAimProfile;
    }
}
