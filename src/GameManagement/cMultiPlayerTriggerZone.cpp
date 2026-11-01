#include "rws/classfactory.h"
#include "GameManagement/cMultiPlayerTriggerZone.h"

namespace GameManagement
{
    const char *cMultiPlayerTriggerZone::RetClassName() const
    {
        return "cMultiPlayerTriggerZone";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cMultiPlayerTriggerZoneRegistrar(
        "cMultiPlayerTriggerZone", cMultiPlayerTriggerZone::MakeNew, 0x70, false);
}
