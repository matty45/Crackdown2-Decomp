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

#include "cd2/memory.h"

// CD2 0x8284A690: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cCampaignPlayerSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCampaignPlayerSpawnPoint;
    }
}
