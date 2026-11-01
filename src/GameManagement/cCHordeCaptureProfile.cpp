#include "rws/classfactory.h"
#include "GameManagement/cCHordeCaptureProfile.h"

namespace GameManagement
{
    const char *cCHordeCaptureProfile::RetClassName() const
    {
        return "cCHordeCaptureProfile";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeCaptureProfileRegistrar(
        "cCHordeCaptureProfile", cCHordeCaptureProfile::MakeNew, 0x48, false);
}
