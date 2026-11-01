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
