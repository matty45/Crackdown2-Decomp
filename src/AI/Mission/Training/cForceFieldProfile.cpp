#include "AI/cForceFieldProfile.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cForceFieldProfile::RetClassName() const
    {
        return "cForceFieldProfile";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cForceFieldProfileRegistrar(
        "cForceFieldProfile", cForceFieldProfile::MakeNew, 0x130, false);
}
