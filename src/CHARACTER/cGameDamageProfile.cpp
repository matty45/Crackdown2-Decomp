#include "CHARACTER/cGameDamageProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cGameDamageProfile::RetClassName() const
    {
        return "cGameDamageProfile";
    }

    static RWS::CClassFactory::CRegistrar cGameDamageProfileRegistrar(
        "cGameDamageProfile", cGameDamageProfile::MakeNew, 0x3C, false);
}
