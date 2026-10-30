#include "PHYSICS/cOnlineOrb.h"
#include "rws/classfactory.h"

namespace PHYSICS
{
    const char *cOnlineOrb::RetClassName() const
    {
        return "cOnlineOrb";
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cOnlineOrbRegistrar(
        "cOnlineOrb", cOnlineOrb::MakeNew, 0x170, false);
}
