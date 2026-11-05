#include "rws/classfactory.h"
#include "GameManagement/cCampaignGameModePrototype.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCampaignGameModePrototype::RetClassName() const
    {
        return "cCampaignGameModePrototype";
    }

    static RWS::CClassFactory::CRegistrar cCampaignGameModePrototypeRegistrar(
        "cCampaignGameModePrototype", cCampaignGameModePrototype::MakeNew, 0x120, false);

    // CD2 0x828574F8: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCampaignGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCampaignGameModePrototype;
    }
}
