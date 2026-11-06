#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "GameManagement/cMiniGameTier.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GameManagement
{
    RWS::CAttributeHandler *cMiniGameTier::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cMiniGameTier;
    }

    static RWS::CClassFactory::CRegistrar cMiniGameTierRegistrar(
        "cMiniGameTier", cMiniGameTier::MakeNew, 0x64, false);

    const char *cMiniGameTier::RetClassName() const
    {
        return "cMiniGameTier";
    }
}
