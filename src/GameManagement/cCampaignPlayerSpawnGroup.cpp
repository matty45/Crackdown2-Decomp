#include "rws/classfactory.h"
#include "GameManagement/cCampaignPlayerSpawnGroup.h"

namespace GameManagement
{
    const char *cCampaignPlayerSpawnGroup::RetClassName() const
    {
        return "cCampaignPlayerSpawnGroup";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCampaignPlayerSpawnGroupRegistrar(
        "cCampaignPlayerSpawnGroup", cCampaignPlayerSpawnGroup::MakeNew, 0xa0, false);
}
