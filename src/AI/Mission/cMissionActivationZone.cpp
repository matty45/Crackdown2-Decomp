#include "AI/cMissionActivationZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionActivationZone::RetClassName() const
    {
        return "cMissionActivationZone";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cMissionActivationZoneRegistrar(
        "cMissionActivationZone", cMissionActivationZone::MakeNew, 0x100, false);
}
