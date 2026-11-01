#include "rws/classfactory.h"
#include "GameManagement/cCampaignGameModePrototype.h"

namespace GameManagement
{
    const char *cCampaignGameModePrototype::RetClassName() const
    {
        return "cCampaignGameModePrototype";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCampaignGameModePrototypeRegistrar(
        "cCampaignGameModePrototype", cCampaignGameModePrototype::MakeNew, 0x120, false);
}
