#include "rws/classfactory.h"
#include "GameManagement/cCHordeProfile.h"

namespace GameManagement
{
    const char *cCHordeProfile::RetClassName() const
    {
        return "cCHordeProfile";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeProfileRegistrar(
        "cCHordeProfile", cCHordeProfile::MakeNew, 0xd8, false);
}
