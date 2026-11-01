#include "rws/classfactory.h"
#include "GameManagement/cGameModeVFXProfile.h"

namespace GameManagement
{
    const char *cGameModeVFXProfile::RetClassName() const
    {
        return "cGameModeVFXProfile";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cGameModeVFXProfileRegistrar(
        "cGameModeVFXProfile", cGameModeVFXProfile::MakeNew, 0x18, false);
}
