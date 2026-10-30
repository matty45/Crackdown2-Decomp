#include "ORB/cSkillPickupProfile.h"
#include "rws/classfactory.h"

namespace ORB
{
    const char *cSkillPickupProfile::RetClassName() const
    {
        return "cSkillPickupProfile";
    }
}

namespace ORB
{
    static RWS::CClassFactory::CRegistrar cSkillPickupProfileRegistrar(
        "cSkillPickupProfile", cSkillPickupProfile::MakeNew, 0xB0, false);
}
