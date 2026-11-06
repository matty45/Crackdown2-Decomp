// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "UI/cAgentColour.h"
#include "rws/classfactory.h"

namespace UI
{
    const char *cAgentColour::RetClassName() const
    {
        return "cAgentColour";
    }

    RWS::CAttributeHandler *cAgentColour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cAgentColour *p = new cAgentColour();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cAgentColourRegistrar(
        "cAgentColour", cAgentColour::MakeNew, 0x28, false);
}
