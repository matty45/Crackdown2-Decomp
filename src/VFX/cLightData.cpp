#include "rws/classfactory.h"
#include "VFX/cLightData.h"

namespace VFX
{
    const char *cLightData::RetClassName() const
    {
        return "cLightData";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cLightDataRegistrar(
        "cLightData", cLightData::MakeNew, 0x1a0, false);
}

#include "cd2/memory.h"

// CD2 0x82800710: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cLightData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLightData;
    }
}
