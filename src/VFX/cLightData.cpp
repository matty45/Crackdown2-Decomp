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
