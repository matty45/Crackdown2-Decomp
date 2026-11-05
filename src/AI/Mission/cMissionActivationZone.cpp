#include "AI/cMissionActivationZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionActivationZone::RetClassName() const
    {
        return "cMissionActivationZone";
    }

    // CD2 0x8248B510: only the member's and the bases' destruction.
    cMissionActivationZone::~cMissionActivationZone()
    {
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cMissionActivationZoneRegistrar(
        "cMissionActivationZone", cMissionActivationZone::MakeNew, 0x100, false);
}
