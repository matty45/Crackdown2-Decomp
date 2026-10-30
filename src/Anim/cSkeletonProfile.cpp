#include "Anim/cSkeletonProfile.h"
#include "rws/classfactory.h"

namespace Anim
{
    const char *cSkeletonProfile::RetClassName() const
    {
        return "cSkeletonProfile";
    }
}

namespace Anim
{
    static RWS::CClassFactory::CRegistrar cSkeletonProfileRegistrar(
        "cSkeletonProfile", cSkeletonProfile::MakeNew, 0x190, false);
}
