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

#include "cd2/memory.h"

// CD2 0x82756D18: the class-factory constructor; the constructor stays out of line.
namespace ORB
{
    RWS::CAttributeHandler *cSkillPickupProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSkillPickupProfile;
    }
}
