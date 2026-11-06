// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
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
