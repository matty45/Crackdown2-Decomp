#include "GameRenderer/cCD2Lighting.h"
#include "rws/classfactory.h"

namespace GameRenderer
{
    const char *cCD2Lighting::RetClassName() const
    {
        return "cCD2Lighting";
    }
}

namespace GameRenderer
{
    static RWS::CClassFactory::CRegistrar cCD2LightingRegistrar(
        "cCD2Lighting", cCD2Lighting::MakeNew, 0x2680, false);
}
