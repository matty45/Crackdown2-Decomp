#include "rws/classfactory.h"
#include "VFX/cSkyDome.h"

namespace VFX
{
    const char *cSkyDome::RetClassName() const
    {
        return "cSkyDome";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cSkyDomeRegistrar(
        "cSkyDome", cSkyDome::MakeNew, 0x4d0, false);
}

#include "cd2/memory.h"

// CD2 0x827B8988: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cSkyDome::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSkyDome;
    }
}
