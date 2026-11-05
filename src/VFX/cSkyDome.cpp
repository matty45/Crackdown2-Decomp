#include "rws/classfactory.h"
#include "VFX/cSkyDome.h"
#include "cd2/memory.h"

namespace VFX
{
    const char *cSkyDome::RetClassName() const
    {
        return "cSkyDome";
    }

    static RWS::CClassFactory::CRegistrar cSkyDomeRegistrar(
        "cSkyDome", cSkyDome::MakeNew, 0x4d0, false);

    // CD2 0x827B8988: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cSkyDome::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSkyDome;
    }
}
