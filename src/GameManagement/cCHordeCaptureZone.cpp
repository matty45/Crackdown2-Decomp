#include "rws/classfactory.h"
#include "GameManagement/cCHordeCaptureZone.h"

namespace GameManagement
{
    const char *cCHordeCaptureZone::RetClassName() const
    {
        return "cCHordeCaptureZone";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeCaptureZoneRegistrar(
        "cCHordeCaptureZone", cCHordeCaptureZone::MakeNew, 0x390, false);
}
