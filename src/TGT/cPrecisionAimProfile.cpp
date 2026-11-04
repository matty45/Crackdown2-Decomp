#include "rws/classfactory.h"
#include "TGT/cPrecisionAimProfile.h"

namespace TGT
{
    const char *cPrecisionAimProfile::RetClassName() const
    {
        return "cPrecisionAimProfile";
    }
}

namespace TGT
{
    static RWS::CClassFactory::CRegistrar cPrecisionAimProfileRegistrar(
        "cPrecisionAimProfile", cPrecisionAimProfile::MakeNew, 0x18, false);
}

#include "cd2/memory.h"

// CD2 0x8277D200: the class-factory constructor; the constructor stays out of line.
namespace TGT
{
    RWS::CAttributeHandler *cPrecisionAimProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cPrecisionAimProfile;
    }
}
