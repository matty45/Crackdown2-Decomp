#include "PHYSICS/cSurfaceProfile.h"
#include "rws/classfactory.h"

namespace PHYSICS
{
    const char *cSurfaceProfile::RetClassName() const
    {
        return "cSurfaceProfile";
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cSurfaceProfileRegistrar(
        "cSurfaceProfile", cSurfaceProfile::MakeNew, 0x80, false);
}
