#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "ORB/cSkillPickupProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace ORB
{
    const char *cSkillPickupProfile::RetClassName() const
    {
        return "cSkillPickupProfile";
    }

    static RWS::CClassFactory::CRegistrar cSkillPickupProfileRegistrar(
        "cSkillPickupProfile", cSkillPickupProfile::MakeNew, 0xB0, false);

    // CD2 0x82756D18: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cSkillPickupProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSkillPickupProfile;
    }
}
