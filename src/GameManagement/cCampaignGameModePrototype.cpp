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

#include "cd2/memory.h"

// CD2 0x828574F8: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cCampaignGameModePrototype::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCampaignGameModePrototype;
    }
}
