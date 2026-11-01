#include "rws/classfactory.h"
#include "VFX/cDepthOfField.h"

namespace VFX
{
    const char *cDepthOfField::RetClassName() const
    {
        return "cDepthOfField";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cDepthOfFieldRegistrar(
        "cDepthOfField", cDepthOfField::MakeNew, 0x8c, false);
}
