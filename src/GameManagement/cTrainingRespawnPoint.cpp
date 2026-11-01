#include "rws/classfactory.h"
#include "GameManagement/cTrainingRespawnPoint.h"

namespace GameManagement
{
    const char *cTrainingRespawnPoint::RetClassName() const
    {
        return "cTrainingRespawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cTrainingRespawnPointRegistrar(
        "cTrainingRespawnPoint", cTrainingRespawnPoint::MakeNew, 0x80, false);
}
