// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cGlobalControlsProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const char *cGlobalControlsProfile::RetClassName() const
    {
        return "cGlobalControlsProfile";
    }

    static RWS::CClassFactory::CRegistrar cGlobalControlsProfileRegistrar(
        "cGlobalControlsProfile", cGlobalControlsProfile::MakeNew, 0x18C, false);

    // CD2 0x82558778: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGlobalControlsProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGlobalControlsProfile;
    }
}
