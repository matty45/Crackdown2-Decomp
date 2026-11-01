#include "rws/classfactory.h"
#include "GameManagement/cCampaignPlayerSpawnPoint.h"

namespace GameManagement
{
    const char *cCampaignPlayerSpawnPoint::RetClassName() const
    {
        return "cCampaignPlayerSpawnPoint";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCampaignPlayerSpawnPointRegistrar(
        "cCampaignPlayerSpawnPoint", cCampaignPlayerSpawnPoint::MakeNew, 0x80, false);
}
