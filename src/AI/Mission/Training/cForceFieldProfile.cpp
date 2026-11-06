// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "AI/cForceFieldProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cForceFieldProfile::RetClassName() const
    {
        return "cForceFieldProfile";
    }

    static RWS::CClassFactory::CRegistrar cForceFieldProfileRegistrar(
        "cForceFieldProfile", cForceFieldProfile::MakeNew, 0x130, false);

    // CD2 0x824889A0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cForceFieldProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cForceFieldProfile(packet);
    }
}
