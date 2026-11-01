#include "rws/classfactory.h"
#include "VFX/cDeityRay.h"

namespace VFX
{
    const char *cDeityRay::RetClassName() const
    {
        return "cDeityRay";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cDeityRayRegistrar(
        "cDeityRay", cDeityRay::MakeNew, 0x6b0, false);
}
