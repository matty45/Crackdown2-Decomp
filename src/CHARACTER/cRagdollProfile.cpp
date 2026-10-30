#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cRagdollProfile::RetClassName() const
    {
        return "cRagdollProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cRagdollProfileRegistrar(
        "cRagdollProfile", cRagdollProfile::MakeNew, 0x3B0, false);
}
