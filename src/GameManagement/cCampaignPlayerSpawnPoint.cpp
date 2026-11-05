#include "rws/classfactory.h"
#include "GameManagement/cCampaignPlayerSpawnPoint.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCampaignPlayerSpawnPoint::RetClassName() const
    {
        return "cCampaignPlayerSpawnPoint";
    }

    static RWS::CClassFactory::CRegistrar cCampaignPlayerSpawnPointRegistrar(
        "cCampaignPlayerSpawnPoint", cCampaignPlayerSpawnPoint::MakeNew, 0x80, false);

    // CD2 0x8284A690: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCampaignPlayerSpawnPoint::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCampaignPlayerSpawnPoint;
    }
}
