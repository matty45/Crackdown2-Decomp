#include "AI/cMissionCompletionZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cMissionCompletionZone::RetClassName() const
    {
        return "cMissionCompletionZone";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cMissionCompletionZoneRegistrar(
        "cMissionCompletionZone", cMissionCompletionZone::MakeNew, 0xF0, false);
}
