#include "rws/classfactory.h"
#include "GameManagement/cHUDPingProfile.h"

namespace GameManagement
{
    const char *cHUDPingProfile::RetClassName() const
    {
        return "cHUDPingProfile";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cHUDPingProfileRegistrar(
        "cHUDPingProfile", cHUDPingProfile::MakeNew, 0x18, false);
}
