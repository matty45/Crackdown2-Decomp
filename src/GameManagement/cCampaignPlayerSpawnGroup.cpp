#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cCampaignPlayerSpawnGroup.h"

namespace GameManagement
{
    const char *cCampaignPlayerSpawnGroup::RetClassName() const
    {
        return "cCampaignPlayerSpawnGroup";
    }

    static RWS::CClassFactory::CRegistrar cCampaignPlayerSpawnGroupRegistrar(
        "cCampaignPlayerSpawnGroup", cCampaignPlayerSpawnGroup::MakeNew, 0xa0, false);
}
